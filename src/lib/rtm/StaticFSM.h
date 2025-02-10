// -*- C++ -*-
/*!
 * @file StaticFSM.h
 * @brief Static FSM framework based on Macho
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2017
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_STATICFSM_H
#define RTC_STATICFSM_H

#include <rtm/RTObject.h>
#include <rtm/Macho.h>
#include <rtm/RingBuffer.h>
#include <rtm/EventBase.h>

/*!
 * @brief State machine definition macros
 *
 * FSM basic structure
 *
 * namespace <FSM name>
 * {
 *   FSM_TOPSTATE(Top)
 *   {
 *     struct Box
 *     {
 *       Box() : <initializer> {}
 *          :
 *       <some operations>
 *          :
 *     };
 *   FSM_STATE(Top);
 *        :
 *   virtual void event_operations() {};
 *        :
 * private:
 *   virtual RTC::ReturnCode_t onInit();
 *   virtual RTC::ReturnCode_t onEntry();
 *   virtual RTC::ReturnCode_t onExit();
 * };
 *
 * FSM_SUBSTATE(OtherState, Top)
 * {
 *   FSM_STATE(OtherState);
 *   virtual void event_operation();
 * private:
 *   virtual RTC::ReturnCode_t onEntry();
 *   virtual RTC::ReturnCode_t onExit();
 * };
 *
 * FSM_SUBSTATE(OtherState2, Top)
 *            : other states
 *
 * }; // end of <FSM name>
 */


/*!
 * @brief Macho's TOPSTATE macro for RTC::Link
 */
#define FSM_TOPSTATE(TOP) \
  struct TOP \
    : public ::RTC::Link< TOP, ::Macho::TopBase< TOP > >

/*!
 * @brief Macho's SUBSTATE macro for RTC::Link
 */
#define FSM_SUBSTATE(STATE, SUPERSTATE) \
  struct STATE \
    : public ::RTC::Link< STATE, SUPERSTATE >

/*!
 * @brief Macho's STATE macro for RTC::Link
 */
#define FSM_STATE(S) \
  public: \
    using SELF = S;                                                     \
    S(::Macho::_StateInstance & instance)                               \
      : ::RTC::Link<S, SUPER>(instance)                                 \
    {                                                                   \
      using MustDeriveFromLink = ::CheckSameType<::RTC::Link<S, SUPER>,    \
                                              LINK>::Check;             \
      static_assert(static_cast<MustDeriveFromLink*>(nullptr)==nullptr, \
                    "dummy assert for suppress warning");               \
    }                                                                   \
    ~S() override {}                                                    \
    static const char * _state_name() { return #S; }                    \
    Box & box() { return *static_cast<Box *>(_box()); }                 \
    friend class ::_VS8_Bug_101615

#define FSM_INIT_VALUE(S) \
   template<> \
   const ::Macho::ID Macho::StateID<S>::value = ::Macho::Machine<typename S::TOP>::theStateCount++;

namespace RTC
{
  /*!
   * @class RTC::Machine class template
   *
   * This is modified version of Macho::Machine class. In this
   * version, the constructor receives RTObject_impl* and it is kept
   * to call callback functions.
   *
   */
  template<class TOP>
  class Machine
    : public Macho::Machine<TOP>
  {
  public:
    Machine(RTC::RTObject_impl* comp)
      : Macho::Machine<TOP>(), rtComponent(comp)
    {
    }
    ~Machine() override = default;
    virtual RingBuffer<EventBase*>& getBuffer()
    {
        return m_buffer;
    }
    virtual void run_event()
    {
        while (m_buffer.readable() > 0)
        {
            EventBase* ebt = m_buffer.get();
            (*ebt)();
            m_buffer.advanceRptr();
            delete ebt;
        }
    }

  private:
    Machine(const Machine<TOP> & other) = delete;
    Machine<TOP> & operator=(const Machine<TOP> & other) = delete;

    template<class C, class P>
    friend class Link;

#ifdef MACHO_SNAPSHOTS
    friend class Macho::Snapshot<TOP>;
#endif
    template<class T> friend class Macho::StateID;

    RTObject_impl* rtComponent;
    RingBuffer<EventBase*> m_buffer;
  };

  /*!
   * @class Link class
   *
   * This is modified version of Macho::Link<C, P> class
   * template. Link class itself State object class.
   *
   * Default state operation entry/init/exit is used internally, and
   * new state operations onEntry/onInit/onExit are added. These onXXX
   * state operations should be override from state implementations.
   *
   */
  template<class C, class P>
  class Link
    : public Macho::Link<C, P>
  {
  protected:
    Link(Macho::_StateInstance & instance)
      : Macho::Link<C, P>(instance), rtComponent(nullptr)
    {
    }
    ~Link() override = default;

    void setrtc()
    {
      if (rtComponent != nullptr) { return; }
      const RTC::Machine<typename P::TOP>* machine =
        dynamic_cast<const RTC::Machine<typename P::TOP>*>(&P::machine());
      if (machine != nullptr) { rtComponent = machine->rtComponent; }
    }
  public:
    using LINK = Link<C, P>;
    
    void entry() override
    {
      setrtc();
      if (rtComponent == nullptr)
        {
          onEntry();
        }
      else
        {
          rtComponent->postOnFsmStateChange(C::_state_name(), RTC::RTC_OK);
          rtComponent->preOnFsmEntry(C::_state_name());
          rtComponent->postOnFsmEntry(C::_state_name(), onEntry());
        }
    }
    void init() override
    {
      setrtc();
      if (rtComponent == nullptr)
        {
          onInit();
        }
      else
        {
          rtComponent->preOnFsmInit(C::_state_name());
          rtComponent->postOnFsmInit(C::_state_name(), onInit());
        }
    }
    void exit() override
    {
      setrtc();
      if (rtComponent == nullptr)
        {
          onExit();
        }
      else
        {
          rtComponent->preOnFsmExit(C::_state_name());
          rtComponent->postOnFsmExit(C::_state_name(), onExit());
          rtComponent->preOnFsmStateChange(C::_state_name());
        }
    }
#if defined(__clang__)
#if defined(_WIN32) || defined(_WIN64)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsuggest-override"
#endif
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winconsistent-missing-override"
#endif
#if defined(__GNUC__) && (__GNUC__ >= 5) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#endif
    // We can't use 'override' insetd of 'virtual', becase these
    // methods are used as TOP LEVEL SUPPER CLASS and SUB CLASS.
    virtual RTC::ReturnCode_t onEntry() { return RTC::RTC_OK; }
    virtual RTC::ReturnCode_t onInit()  { return RTC::RTC_OK; }
    virtual RTC::ReturnCode_t onExit()  { return RTC::RTC_OK; }
#if defined(__GNUC__) && (__GNUC__ >= 5) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
#if defined(__clang__)
#pragma clang diagnostic pop
#if defined(_WIN32) || defined(_WIN64)
#pragma clang diagnostic pop
#endif
#endif

    RTObject_impl* rtComponent;
  };
} // namespace RTC
#endif // RTC_STATICFSM_H
