// -*- C++ -*-
/*!
 * @file MonitoringImpl.h
 * @brief MonitoringImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef MONITORING_IMPL_H
#define MONITORING_IMPL_H


#include <doil/ImplBase.h>
#include <IMonitoring.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class MonitoringImpl
   * @brief Monitoring試験用インプリメントクラス
   * @else
   * @class MonitoringImpl
   * @brief Monitoring implementation class for MonitoringServant' unittest.
   * @endif
   */

  class MonitoringImpl
   : public virtual doil::ImplBase,
     public virtual ::SDOPackage::Local::IMonitoring

  {
  public:
    MonitoringImpl();
    MonitoringImpl(Logger& aLogger);

    virtual ~MonitoringImpl();



    const char* id() { return "Monitoring"; }
    const char* name() { return m_name; }
    void incRef() { refcount++; }
    void decRef() { refcount--; }
  private:
    static int count;
    char m_name[32];
    int refcount;
    Logger *m_logger;
  };

}; // namespace Servant
}; // namespace UnitTest

#endif  // 
