/**
 * Copyright 2005 Eduard Etti
*/
#include "hrtm/statechart.h"
#include "hrtm/logger.h"

#define LOGGER "StateChart"

using namespace hrtm;  // NOLINT
using namespace hrtm::sc;  // NOLINT

////////////////////////////////////////////////////////////////////////////////
// Implementation for State
StateInfo & StateBase::get_info(MachineBase & machine) {
  // Look first in machine for existing StateInfo.
  StateInfo * & info = machine.get_info(key());
  if (!info) {
    info = new RootStateInfo(machine, 0);
  }
  return *info;
}

void StateBase::shutdown() {
  state_info_.machine().shutdown();
}

void StateBase::restore(StateInfo & current) {
  state_info_.machine().current_state_ = &current;
}

////////////////////////////////////////////////////////////////////////////////
// StateInfo implementation
StateInfo::StateInfo(MachineBase & machine, StateInfo * parent)
  : machine_(machine)
  , instance_(0)
  , history_(0)
  , parent_(parent)
  , data_(0)
  , data_place(0) {}

StateInfo::~StateInfo() {
  if (data_place) {
    ::operator delete(data_place);
  }

  delete instance_;
}

void StateInfo::on_entry(StateInfo & previous, bool first) {
  // Only Root has no parent
  if (!parent_) {
    return;
  }
  // first entry or previous state is not substate -> perform entry
  if (first || !previous.is_child(*this)) {
    parent_->on_entry(previous, false);
    // Could be set from outside or persistent (or EmptyData)
    if (!data_) {
      create_data();
    }
    HRTM_DEBUG(LOGGER, name() <<  ": entry");
    instance_->on_entry();
  }
}

void StateInfo::on_exit(StateInfo & next) {
  // Only Root has no parent
  if (!parent_) {
    return;
  }
  // self transition or next state is not substate -> perform exit
  if (this == &next || !next.is_child(*this)) {
    HRTM_DEBUG(LOGGER, name() << ": exit");
    instance_->on_exit();
    instance_->delete_data(*this);
    parent_->on_exit(next);
  }
}

void StateInfo::on_init(bool history) {
  if (history && history_) {
    HRTM_DEBUG(LOGGER, name() << ": history transition to: " <<
       history_->name());
    machine_.set_pending_state(*history_, true, 0);
  } else {
    HRTM_DEBUG(LOGGER, name() << ": init");
    instance_->on_init();
  }
  history_ = 0;
}

void StateInfo::copy(StateInfo & original) {
  if (original.history_) {
    StateInfo * history = machine_.get_info(original.history_->key());
    assert(history);
    set_history(history);
  }

  if (original.data_) {
    clone_data(original.data_);
  }
}

StateInfo * StateInfo::clone(MachineBase & new_machine) {
  assert(!new_machine.get_info(key()));

  StateInfo * parent = 0;
  if (parent_) {
    // Tell other machine to clone parent first.
    parent = new_machine.create_clone(parent_->key(), parent_);
  }
  StateInfo * clone = create(new_machine, parent);
  return clone;
}

////////////////////////////////////////////////////////////////////////////////
// Base class for Machine objects.
MachineBase::MachineBase()
  : current_state_(0)
  , pending_state_(0)
  , pending_data_(0)
  , pending_history_(false)
  , pending_event_(0) {}

MachineBase::~MachineBase() {
  assert(!pending_data_);

  delete[] states_;
  delete pending_event_;
}

void MachineBase::set_state(StateInfo & info, bool history, void * data) {
  set_pending_state(info, history, data);
  perform_pending();
}

void MachineBase::set_state(const StateAlias & state, bool history) {
  set_pending_state(state.get_info(*this), history, state.take_data());
  perform_pending();
}

void MachineBase::start(StateInfo & info, void * data) {
  HRTM_DEBUG(LOGGER, "Starting Machine");

  // Start with Root state
  current_state_ = &StateBase::get_info(*this);
  // Then go to state
  set_state(info, false, data);
}

void MachineBase::shutdown() {
  assert(!pending_state_);

  HRTM_DEBUG(LOGGER, "Shutting down Machine");
  // Performs exit actions by going to Root (=State) state.
  set_state(StateBase::get_info(*this), false, 0);
  current_state_ = 0;
}

void MachineBase::allocate(unsigned int count) {
  states_ = new StateInfo *[count];
  for (unsigned int i = 0; i < count; ++i) {
    states_[i] = 0;
  }
}

void MachineBase::free(unsigned int count) {
  // Free from end of list, so that child states are freed first
  unsigned int i = count;
  while (i > 0) {
    --i;
    delete states_[i];
    states_[i] = 0;
  }
}

void MachineBase::copy(StateInfo ** other, unsigned int count) {
  Key i;

  // Create StateInfo objects
  for (i = 0; i < count; ++i) {
    create_clone(i, other[i]);
  }
  // Copy StateInfo object's state
  for (i = 0; i < count; ++i) {
    StateInfo * state = states_[i];
    if (state) {
      assert(other[i]);
      state->copy(*other[i]);
    }
  }
}

StateInfo * MachineBase::create_clone(Key key, StateInfo * original) {
  StateInfo * & clone = get_info(key);

  // Object already created?
  if (!clone && original) {
    clone = original->clone(*this);
  }
  return clone;
}

void MachineBase::add_deferred_event(EventBase * event,
    const std::string& name) {
  assert(event);

  try {
    EventQueue::iterator queue = deferred_events_.find(name);
    if (queue != deferred_events_.end()) {
      HRTM_DEBUG(LOGGER, name << " is already deferred.");
      return;
    }
    deferred_events_[name] = event;
    deferred_names_.push_back(name);
  } catch (std::exception& ex) {  // NOLINT
    HRTM_WARNING(LOGGER, "Can't add defferd event by " << ex.what());
  }
}

void MachineBase::perform_pending() {
  assert(current_state_);

  if (pending_state_) {
    // Loop here because init actions might change state again.
    while (pending_state_) {
      HRTM_DEBUG(LOGGER, current_state_->name() << ": transition to: " <<
          pending_state_->name());
      // Perform exit actions (which exactly depends on new state).
      current_state_->on_exit(*pending_state_);
      // Store history information for previous state now.
      // Previous state will be used for deep history.
      current_state_->set_history_super(*current_state_);
      StateInfo * previous = current_state_;
      current_state_ = pending_state_;
      if (pending_data_) {
        current_state_->set_data(pending_data_);
      }
      // Perform entry actions (which exactly depends on previous state).
      current_state_->on_entry(*previous);
      // State transition complete.
      // Clear 'pending' information just now so that set_state would assert
      // in exits and entries, but not in init.
      pending_state_ = 0;
      pending_data_ = 0;
      bool history = pending_history_;
      pending_history_ = false;
      // "init" may change state again.
      current_state_->on_init(history);
      assert("Init may only transition to proper substates" &&
          (!pending_state_ ||
           (pending_state_->is_child(*current_state_) &&
           (current_state_ != pending_state_))));
      // Perform pending event
      perform_pending_event();
      // Perform deferred events
      perform_deferred_events();
    }  // while (pending_state_)
  } else {  // if (pending_state_)
    // Perform pending event
    perform_pending_event();
  }
}

void MachineBase::perform_pending_event() {
  if (pending_event_) {
    EventBase * event = pending_event_;
    pending_event_ = 0;
    event->dispatch(*current_state_);
    delete event;
  }
}

void MachineBase::perform_deferred_events() {
  if (deferred_events_.empty()) {
    return;
  }
  for (EventNames::iterator i = deferred_names_.begin();
    i != deferred_names_.end(); ++i) {
    if (current_state_) {
      deferred_events_[(*i)]->dispatch(*current_state_);
      delete deferred_events_[(*i)];
    }
  }
  deferred_events_.clear();
  deferred_names_.clear();
}
