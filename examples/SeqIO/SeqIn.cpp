// -*- C++ -*-
/*!
 * @file SeqIn.cpp
 * @brief SeqIn component
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * $Id: SeqIn.cpp,v 1.1.1.1 2005-05-12 09:06:20 n-ando Exp $
 */



#include "SeqIn.h"

using namespace std;

SeqIn::SeqIn(RtcManager* manager)
  : RtcBase(manager) ,
    m_DoubleIn("Double", m_Double),
	m_FloatIn("Float", m_Float),
    m_LongIn("Long", m_Long),
	m_ShortIn("Short", m_Short),
    m_DoubleSeqIn("DoubleSeq", m_DoubleSeq),
	m_FloatSeqIn("FloatSeq", m_FloatSeq),
    m_LongSeqIn("LongSeq", m_LongSeq),
	m_ShortSeqIn("ShortSeq", m_ShortSeq)

{
  registerInPort(m_DoubleIn);
  registerInPort(m_FloatIn);
  registerInPort(m_LongIn);
  registerInPort(m_ShortIn);
  registerInPort(m_DoubleSeqIn);
  registerInPort(m_FloatSeqIn);
  registerInPort(m_LongSeqIn);
  registerInPort(m_ShortSeqIn);

  appendAlias("example/SeqIn|rtc");
}

RtmRes SeqIn::rtc_ready_do()
{
}

RtmRes SeqIn::rtc_active_do()
{
  m_DoubleIn.read();
  m_FloatIn.read();
  m_LongIn.read();
  m_ShortIn.read();
  m_DoubleSeqIn.read();
  m_FloatSeqIn.read();
  m_LongSeqIn.read();
  m_ShortSeqIn.read();

  int h_col(4);
  int col(13);
  int all_col = h_col + (col * 4);
  int all_row(0);

  int d_size(1);
  int f_size(1);
  int l_size(1);
  int s_size(1);

  int ds_size(m_DoubleSeq.data.length());
  int fs_size(m_FloatSeq.data.length());
  int ls_size(m_LongSeq.data.length());
  int ss_size(m_ShortSeq.data.length());
  
  int max_size;

  std::vector<int> in_size;
  std::vector<int>::iterator it;
  in_size.reserve(8);
  in_size.push_back(d_size);
  in_size.push_back(f_size);
  in_size.push_back(l_size);
  in_size.push_back(s_size);
  in_size.push_back(ds_size);
  in_size.push_back(fs_size);
  in_size.push_back(ls_size);
  in_size.push_back(ss_size);

  it = std::max_element(in_size.begin(), in_size.end());
		
  max_size = *it;

  std::cout.width(h_col + (col * 4));
  std::cout.fill('-');
  std::cout << "-" << std::endl; all_row++;

  std::cout.width(h_col);
  std::cout.setf(ios::right, ios::adjustfield);
  std::cout.fill(' ');
  std::cout << " ";   
  std::cout.width(col);
  std::cout.setf(ios::right, ios::adjustfield);
  std::cout.fill(' ');
  std::cout << "Double";
  std::cout.width(col);
  std::cout.setf(ios::right, ios::adjustfield);
  std::cout.fill(' ');
  std::cout << "Float";
  std::cout.width(col);
  std::cout.setf(ios::right, ios::adjustfield);
  std::cout.fill(' ');
  std::cout << "Long";
  std::cout.width(col);
  std::cout.setf(ios::right, ios::adjustfield);
  std::cout.fill(' ');
  std::cout << "Short";
  std::cout << endl; all_row++;

  std::cout.width(all_col);
  std::cout.fill('-');
  std::cout << "-" << std::endl;  all_row++;

  for (int i = 0; i < (all_col - 10)/ 2; i++)
	std::cout << " ";
  std::cout << "Basic type";
  for (int i = 0; i < (all_col - 10)/ 2; i++)
	std::cout << " ";
  std::cout << endl; all_row++;

  std::cout.width(h_col + (col * 4));
  std::cout.fill('-');
  std::cout << "-" << std::endl; all_row++;

  std::cout.width(h_col);
  std::cout.setf(ios::right, ios::adjustfield);
  std::cout.fill(' ');
  std::cout << " ";   
  std::cout.width(col);
  std::cout.setf(ios::right, ios::adjustfield);
  std::cout.fill(' ');
  std::cout << m_Double.data;
  std::cout.width(col);
  std::cout.setf(ios::right, ios::adjustfield);
  std::cout.fill(' ');
  std::cout << m_Float.data;
  std::cout.width(col);
  std::cout.setf(ios::right, ios::adjustfield);
  std::cout.fill(' ');
  std::cout << m_Long.data;
  std::cout.width(col);
  std::cout.setf(ios::right, ios::adjustfield);
  std::cout.fill(' ');
  std::cout << m_Short.data;
  std::cout << std::endl; all_row++;

  std::cout.width(all_col);
  std::cout.fill('-');
  std::cout << "-" << std::endl; all_row++;

  for (int i = 0; i < (all_col - 13)/ 2; i++)
	std::cout << " ";
  std::cout << "Sequence type";
  for (int i = 0; i < (all_col - 13)/ 2; i++)
	std::cout << " ";
  std::cout << endl; all_row++;

  std::cout.width(all_col);
  std::cout.fill('-');
  std::cout << "-" << std::endl; all_row++;

  for (int i = 0; i < max_size; i++)
	{
	  std::cout.width(h_col - 2);
	  std::cout.setf(ios::right, ios::adjustfield);
	  std::cout.fill(' ');
	  std::cout << i;
	  std::cout.width(2);
	  std::cout << ": ";

	  std::cout.width(col);
	  std::cout.setf(ios::right, ios::adjustfield);
	  std::cout.fill(' ');
	  if (i < ds_size)
		{
		  std::cout << m_DoubleSeq.data[i];
		}
	  else
		{
		  std::cout << "-";
		}

	  std::cout.width(col);
	  std::cout.setf(ios::right, ios::adjustfield);
	  std::cout.fill(' ');
	  if (i < fs_size)
		{
		  std::cout << m_FloatSeq.data[i];
		}
	  else
		{
		  std::cout << "-";
		}

	  std::cout.width(col);
	  std::cout.setf(ios::right, ios::adjustfield);
	  std::cout.fill(' ');
	  if (i < ls_size)
		{
		  std::cout << m_LongSeq.data[i];
		}
	  else
		{
		  std::cout << "-";
		}

	  std::cout.width(col);
	  std::cout.setf(ios::right, ios::adjustfield);
	  std::cout.fill(' ');
	  if (i < ss_size)
		{
		  std::cout << m_ShortSeq.data[i];
		}
	  else
		{
		  std::cout << "-";
		}

	  std::cout << endl; all_row++;
	}

  for (int i = 0 ; i < all_row; i++)
	{
	  std::cout << "[A\r";
	}

  return RTM_OK;
}


extern "C" {
  
  RtcBase* SeqInNew(RtcManager* manager)
  {
	return new SeqIn(manager);
  }
  
  
  void SeqInDelete(RtcBase* p)
  {
	delete (SeqIn *)p;
	return;
  }
  
  
  void SeqInInit(RtcManager* manager)
  {
	RtcModuleProfile profile(seqin_spec);
	manager->registerComponent(profile, SeqInNew, SeqInDelete);
  }
};

