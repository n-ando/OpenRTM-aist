// A simple simulation of an microwave oven:
// Timer can be programmed in minutes, last mode will be resumed if opened.
//
// Compile like this:
// g++ Macho.cpp Microwave.cpp

#ifndef MICROWAVEFSM_H
#define MICROWAVEFSM_H

#include <iostream>
#include <rtm/StaticFSM.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/RTC.h>

class Microwave;

// Simple microwave simulation
namespace MicrowaveFsm
{

  /*!
   * @if jp
   * @brief 電子レンジ状態マシンサンプル
   *
   * Macho に付属の Microwave FSM のサンプル
   *
   * @else
   * @brief Microwave state machine sample
   *
   * Microwave FSM example included in Macho
   *
   * @endif
   */

  /*!
   * @if jp
   * @class TOP状態
   *
   *
   * @else
   * @brief TOP state
   *
   * @endif
   */
  FSM_TOPSTATE(Top)
  {
    // Top state data (visible to all substates)
    struct Box
    {
      Box()  {}
      void printTimer()
      {
        std::cout << "  Timer set to ";
        std::cout << myCookingTime << " minutes" << std::endl;
      }
      void incrementTimer() { ++myCookingTime; }
      void decrementTimer() { -- myCookingTime; }
      void resetTimer() { myCookingTime = 0; }
      int getRemainingTime() { return myCookingTime; }
    private:
      int myCookingTime{0};
    };

    FSM_STATE(Top);

    // Machine's event protocol
    virtual void open() {}
    virtual void close() {}
    virtual void minute(RTC::TimedLong /* time */) {}
    virtual void start() {}		// Start cooking
    virtual void stop() {}		// Stop cooking
    virtual void tick() {}		// Minute has passed

  private:
    RTC::ReturnCode_t onInit() override;
    RTC::ReturnCode_t onEntry() override;
    RTC::ReturnCode_t onExit() override;
  };

  //============================================================
  // Microwave has been opened
  FSM_SUBSTATE(Disabled, Top)
  {
    FSM_STATE(Disabled);

    // Event handler
    void close() override;

  private:
    RTC::ReturnCode_t onEntry() override;
    RTC::ReturnCode_t onExit() override;
  };

  //============================================================
  // Microwave is ready
  FSM_SUBSTATE(Operational, Top)
  {
    FSM_STATE(Operational);

    // State has history enabled
    DEEPHISTORY();

    // Event handler
    void open() override;
    void stop() override;

  private:
    RTC::ReturnCode_t onInit() override;
  };

  //============================================================
  // Microwave is idling
  FSM_SUBSTATE(Idle, Operational)
  {
    FSM_STATE(Idle);

    void minute(RTC::TimedLong time) override;

  private:
    RTC::ReturnCode_t onEntry() override;
  };

  //============================================================
  // Microwave is being programmed
  FSM_SUBSTATE(Programmed, Operational)
  {
    FSM_STATE(Programmed);

    void minute(RTC::TimedLong time) override;
    void start() override;

  private:
    RTC::ReturnCode_t onEntry() override;
    RTC::ReturnCode_t onInit() override;
    RTC::ReturnCode_t onExit() override;
  };

  //============================================================
  // Microwave is heating
  FSM_SUBSTATE(Cooking, Programmed)
  {
    FSM_STATE(Cooking);

    void tick() override;

  private:
    RTC::ReturnCode_t onEntry() override;
    RTC::ReturnCode_t onExit() override;
  };
} // namespace MicrowaveFsm


#endif // MICROWAVEFSM_H
