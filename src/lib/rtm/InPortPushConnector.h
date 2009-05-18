/*! -*- C++ -*-
 *
 * @file InPortPushConnector.h
 * @brief Push type connector class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_INPORTPUSHCONNECTOR_H
#define RTC_INPORTPUSHCONNECTOR_H

#include <rtm/InPortConnector.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherBase.h>

namespace RTC
{
  class InPortProvider;

  class InPortPushConnector
    : public InPortConnector
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * InPortPushConnector �� InPortConsumer �ν�ͭ������ġ�
     * �������äơ�InPortPushConnector ������ˤϡ�InPortConsumer��Ʊ����
     * ���Ρ��������롣
     *
     * @param profile ConnectorProfile
     * @param consumer InPortConsumer
     *
     * @else
     * @brief Constructor
     *
     * InPortPushConnector assume ownership of InPortConsumer.
     * Therefore, InPortConsumer will be deleted when InPortPushConnector
     * is destructed.
     *
     * @param profile ConnectorProfile
     * @param consumer InPortConsumer
     *
     * @endif
     */
    InPortPushConnector(Profile profile, InPortProvider* provider,
                        CdrBufferBase* buffer = 0);

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * disconnect() ���ƤФ졢consumer, publisher, buffer �����Ρ��������롣
     *
     * @else
     *
     * @brief Destructor
     *
     * This operation calls disconnect(), which destructs and deletes
     * the consumer, the publisher and the buffer.
     *
     * @endif
     */
    virtual ~InPortPushConnector();

    /*!
     * @if jp
     * @brief �ǡ����ν񤭹���
     *
     * Publisher���Ф��ƥǡ�����񤭹��ߡ�����ˤ���б�����InPort��
     * �ǡ�����ž������롣
     *
     * @else
     *
     * @brief Writing data
     *
     * This operation writes data into publisher and then the data
     * will be transferred to correspondent InPort.
     *
     * @endif
     */
    virtual ReturnCode read(cdrMemoryStream& data);

    /*!
     * @if jp
     * @brief ��³���
     *
     * consumer, publisher, buffer �����Ρ��������롣
     *
     * @else
     *
     * @brief disconnect
     *
     * This operation destruct and delete the consumer, the publisher
     * and the buffer.
     *
     * @endif
     */
    virtual ReturnCode disconnect();

    virtual void activate(){}; // do nothing
    virtual void deactivate(){}; // do nothing
  protected:
    /*!
     * @if jp
     * @brief Buffer������
     * @else
     * @brief create buffer
     * @endif
     */
    virtual CdrBufferBase* createBuffer(Profile& profile);

  private:
    /*!
     * @if jp
     * @brief InPortConsumer �ؤΥݥ���
     * @else
     * @brief the pointer to the InPortConsumer
     * @endif
     */
    InPortProvider* m_provider;
  };
}; // namespace RTC

#endif  // RTC_PUSH_CONNECTOR_H