// -*- C++ -*-
/*!
 * @file  Phantom.cpp
 * @brief PHANToM component
 * @date $Date$
 *
 * $Id$
 */

#include <iostream>
#include "Phantom.h"
#include "VectorConvert.h"

#define BILATERAL 0
#define JOYSTICK 1
#define THRESHOLD 10.0

// Module specification
static const char* phantom_spec[] =
  {
    "implementation_id", "Phantom",
    "type_name",         "Phantom",
    "description",       "PHANToM component",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.force_gain", "1.0,1.0,1.0",
    "conf.default.cnt_mode", "joystick",
    "conf.default.coordinate", "0,1,2,3,4,5",
    // Widget
    "conf.__widget__.force_gain", "slider.0.1",
    "conf.__widget__.cnt_mode", "radio",
    "conf.__widget__.coordinate", "text",
    // Constraints
    "conf.__constraints__.force_gain", "0.0<x<100.0",
    "conf.__constraints__.cnt_mode", "(joystick,bilateral)",
    "conf.joystick_xyz.force_gain", "1.0,1.0,1.0",
    "conf.joystick_xyz.cnt_mode", "joystick",
    "conf.joystick_xyz.coordinate", "0,1,2,3,4,5",
    "conf.joystick_xzy.force_gain", "1.0,1.0,1.0",
    "conf.joystick_xzy.cnt_mode", "joystick",
    "conf.joystick_xzy.coordinate", "0,2,1,3,4,5",
    ""
  };

HDCallbackCode HDCALLBACK DevicePositionCallback(void *pUserData);

static HDdouble g_force[FORCE_ELEMENT] = {0.0, 0.0, 0.0};
static hduVector3Dd g_anchor;

HDdouble g_position[POS_ELEMENT];
HDdouble g_angle[RPY_ELEMENT];
HDint g_button_1_flag = B_OFF;
HDint g_button_2_flag = B_OFF;
HDint g_control_mode = BILATERAL;


/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Phantom::Phantom(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    m_refIn("ref", m_ref),
    m_curOut("cur", m_cur),
    m_last_mode("bilateral")
{
}

/*!
 * @brief destructor
 */
Phantom::~Phantom()
{
}



RTC::ReturnCode_t Phantom::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // Set InPort buffers
  addInPort("ref", m_refIn);
  
  // Set OutPort buffer
  addOutPort("cur", m_curOut);
  
  // Bind variables and configuration variable
  bindParameter("force_gain", m_force_gain, "1.0,1.0,1.0");
  bindParameter("cnt_mode", m_cnt_mode, "joystick");
  bindParameter("coordinate", m_coordinate, "0,1,2,3,4,5");
  
  m_cur.data.length(POS_ELEMENT+RPY_ELEMENT);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Phantom::onActivated(RTC::UniqueId ec_id)
{
  HDErrorInfo error;
  m_hHD = hdInitDevice(HD_DEFAULT_DEVICE);
  if (HD_DEVICE_ERROR(error = hdGetError())) {
    hduPrintError(stderr, &error, "Failed to initialize haptic device");
    std::exit(-1);
  }

  /***********************************************************************
    Schedule the haptic callback function for continuously monitoring the
    button state and rendering the anchored spring force
  ************************************************************************/
  m_CallbackHandle = hdScheduleAsynchronous(DevicePositionCallback,
					   0, HD_MAX_SCHEDULER_PRIORITY);
  
  hdEnable(HD_FORCE_OUTPUT);

  hdStartScheduler();

  if (HD_DEVICE_ERROR(error = hdGetError())) {
    hduPrintError(stderr, &error, "Failed to start the scheduler");
    std::exit(-1);
  }

  //  m_phantommode.set_mode_reference(m_cnt_mode);
  m_last_mode = m_cnt_mode;
  g_button_1_flag = B_OFF;

  for(int i = 0; i < POS_ELEMENT+RPY_ELEMENT; ++i) {
    m_cur.data[i] = 0.0;
  }
  m_last_mode = m_cnt_mode;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Phantom::onDeactivated(RTC::UniqueId ec_id)
{
  /**********************************************************************
    Cleanup by stopping the haptics loop, unscheduling the asynchronous
    callback and disabling the device
  ***********************************************************************/
  hdStopScheduler();
  hdUnschedule(m_CallbackHandle);  
  hdDisableDevice(m_hHD);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Phantom::onExecute(RTC::UniqueId ec_id)
{
  g_control_mode = m_cnt_mode == "bilateral" ? BILATERAL : JOYSTICK;

  if (m_cnt_mode != m_last_mode) {
    m_last_mode = m_cnt_mode;
    g_button_1_flag = B_OFF;
  }

  if (m_refIn.isNew()) {
    m_refIn.read();
    float temp_force[FORCE_ELEMENT];
    if(m_ref.data.length() >= FORCE_ELEMENT) {
      for(int i = 0; i < FORCE_ELEMENT; i++) {
	temp_force[i] = (HDdouble)(m_ref.data[i] * m_force_gain[i]);
      }
      g_force[0] = (HDdouble)(-(temp_force[1]));
      g_force[1] = (HDdouble)(temp_force[2]);
      g_force[2] = (HDdouble)(-(temp_force[0]));
    }
  }

  if(m_cnt_mode == "bilateral") {
    if(g_button_1_flag == B_FREE) {
      m_cur.data[0] = (float)(-g_position[2]);
      m_cur.data[1] = (float)(-g_position[0]);
      m_cur.data[2] = (float)( g_position[1]);
    }
  }
  else if(m_cnt_mode == "joystick") {
    float temp_pos[POS_ELEMENT];
    for(int i = 0; i < POS_ELEMENT+RPY_ELEMENT; i++) {
      m_cur.data[i] = 0.0;
    }
    if(g_button_1_flag == B_FREE) {
      for(int i = 0; i < POS_ELEMENT; i++) {
	temp_pos[i] = (float)(g_position[m_coordinate[i]]-g_anchor[m_coordinate[i]]);
      }
      if (m_coordinate[1] == 2) {
	temp_pos[1] = -(temp_pos[1]);
      }
    }

    double dis = sqrt(powf(temp_pos[0], 2) + powf(temp_pos[1], 2) + powf(temp_pos[2], 2));

    if(dis > THRESHOLD) {
      for(int i = 0; i < POS_ELEMENT; i++) {
	m_cur.data[i] = temp_pos[i];
      }
    }
  }
  m_curOut.write();
  return RTC::RTC_OK;
}

HDCallbackCode HDCALLBACK DevicePositionCallback(void *pUserData)
{
  static HDboolean bRenderForce = FALSE;
  static HDdouble gSpringStiffness = 0.1;

  HDErrorInfo error;
  hduVector3Dd force(0.0, 0.0, 0.0);
  hduVector3Dd position;
  HDint nCurrentButtons, nLastButtons;

  hdBeginFrame(hdGetCurrentDevice()); 

  // get state
  hdGetDoublev(HD_CURRENT_POSITION, position);
  hdGetIntegerv(HD_CURRENT_BUTTONS, &nCurrentButtons);
  hdGetIntegerv(HD_LAST_BUTTONS, &nLastButtons);

  if((nCurrentButtons & HD_DEVICE_BUTTON_1) != 0 &&
     (nLastButtons & HD_DEVICE_BUTTON_1) == 0)
    {
      // button down
      bRenderForce = FALSE;
      g_button_1_flag = B_ON;
      hdSetDoublev(HD_CURRENT_FORCE,force);
    }
  else if((nCurrentButtons & HD_DEVICE_BUTTON_1) != 0 &&
	  (nLastButtons & HD_DEVICE_BUTTON_1) != 0)
    {
      // Have pushed the button
      memcpy(g_anchor, position, sizeof(hduVector3Dd));
      g_button_1_flag = B_PUSH;
      bRenderForce = TRUE;
    }
  else if((nCurrentButtons & HD_DEVICE_BUTTON_1) == 0 &&
	  (nLastButtons & HD_DEVICE_BUTTON_1) != 0)
    {
      // Detected button up
      g_button_1_flag = B_FREE;
      bRenderForce = FALSE;
    }

  if((nCurrentButtons & HD_DEVICE_BUTTON_2) != 0 &&
     (nLastButtons & HD_DEVICE_BUTTON_2) == 0) {
    g_button_2_flag = B_ON;
  }
  else if((nCurrentButtons & HD_DEVICE_BUTTON_2) != 0 &&
	  (nLastButtons & HD_DEVICE_BUTTON_2) != 0) {
    g_button_2_flag = B_PUSH;
  }
  else if((nCurrentButtons & HD_DEVICE_BUTTON_2) == 0 &&
	  (nLastButtons & HD_DEVICE_BUTTON_2) != 0) {
    g_button_2_flag = B_OFF;
  }
  
  if (g_control_mode == BILATERAL && g_button_1_flag == B_FREE) {
    hduVecSubtract(force, force, g_force);
    hdSetDoublev(HD_CURRENT_FORCE, force);
  }
  else if (g_control_mode == JOYSTICK && g_button_1_flag == B_FREE) {
    hduVecSubtract(force, g_anchor, position);
    hduVecScaleInPlace(force, gSpringStiffness);
    // hduVecSubtract(force, force, g_force);
    hdSetDoublev(HD_CURRENT_FORCE, force);
  }

  hdGetDoublev(HD_CURRENT_POSITION, g_position);
  hdGetDoublev(HD_CURRENT_GIMBAL_ANGLES, g_angle);

  hdEndFrame(hdGetCurrentDevice());
  
  // Check if an error occurred while attempting to render the force
  if (HD_DEVICE_ERROR(error = hdGetError()))
    {
      if (hduIsForceError(&error))
        {
	  bRenderForce = FALSE;
        }
      else if (hduIsSchedulerError(&error))
        {
	  return HD_CALLBACK_DONE;
        }
    }
  
  return HD_CALLBACK_CONTINUE;
}



extern "C"
{
 
  void PhantomInit(RTC::Manager* manager)
  {
    coil::Properties profile(phantom_spec);
    manager->registerFactory(profile,
                             RTC::Create<Phantom>,
                             RTC::Delete<Phantom>);
  }
  
};


