// -*- C++ -*-
/*!
 * @file Factory.h
 * @brief generic Factory template class
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

#ifndef COIL_FACTORY_H
#define COIL_FACTORY_H

#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <coil/Singleton.h>

namespace coil
{
  template <class AbstractClass, class ConcreteClass>
  AbstractClass* Creator()
  {
    return new ConcreteClass();
  }

  template <class AbstractClass, class ConcreteClass>
  void Destructor(AbstractClass*& obj)
  {
    if (obj == 0) { return; }
    ConcreteClass* tmp = dynamic_cast<ConcreteClass*>(obj);
    if (tmp == 0) { return; }
    delete obj;
    obj = 0;
  }

  template <
    class AbstractClass,
    typename Identifier = std::string,
    typename Compare = std::less<Identifier>,
    typename Creator = AbstractClass* (*)(),
    typename Destructor = void (*)(AbstractClass*&)
    >
  class Factory
  {
    class FactoryEntry;
  public:

    typedef std::map<Identifier, FactoryEntry> FactoryMap;
    typedef typename FactoryMap::iterator     FactoryMapIt;
    
    enum ReturnCode
      {
        FACTORY_OK,
        FACTORY_ERROR,
        ALREADY_EXISTS,
        NOT_FOUND,
        INVALID_ARG,
        UNKNOWN_ERROR
      };

    bool hasFactory(const Identifier& id)
    {
      if (m_creators.count(id) == 0) { return false; }
      return true;
    }

    std::vector<Identifier> getIdentifiers()
    {
      std::vector<Identifier> idlist;
      idlist.reserve(m_creators.size());

      FactoryMapIt it(m_creators.begin());
      FactoryMapIt it_end(m_creators.end());

      while (it != it_end)
        {
          idlist.push_back(it->first);
          ++it;
        }
      return idlist;
    }

    ReturnCode addFactory(const Identifier& id,
                          Creator creator,
                          Destructor destructor)
    {
      if (creator == 0 || destructor == 0) { return INVALID_ARG; }
      if (m_creators.count(id) != 0) { return ALREADY_EXISTS; }
      FactoryEntry f(creator, destructor);
      m_creators[id] = f;
      return FACTORY_OK;
    }

    ReturnCode removeFactory(const Identifier& id)
    {
      if (m_creators.count(id) == 0) { return NOT_FOUND; }

      m_creators.erase(id);
      return FACTORY_OK;
    }

    AbstractClass* createObject(const Identifier& id)
    {
      if (m_creators.count(id) == 0) { return 0; }
      return m_creators[id].creator_();
    }

    void deleteObject(const Identifier& id, AbstractClass*& obj)
    {
      if (m_creators.count(id) == 0) { return; }
      m_creators[id].destructor_(obj);
    }

    void deleteObject(AbstractClass*& obj)
    {
      FactoryMapIt it(m_creators.begin());
      FactoryMapIt it_end(m_creators.end());

      while (it != it_end)
        {
          it->second.destructor_(obj);
          ++it;
        }
    }

  private:
    class FactoryEntry
    {
    public:
      explicit FactoryEntry()
      {
      }
      FactoryEntry(Creator creator, Destructor destructor)
        : creator_(creator), destructor_(destructor)
      {
      }
      Creator creator_;
      Destructor destructor_;
    };
    FactoryMap m_creators;
  };



  template <
    class AbstractClass,
    typename Identifier = std::string,
    typename Compare = std::less<Identifier>,
    typename Creator = AbstractClass* (*)(),
    typename Destructor = void (*)(AbstractClass*&)
    >
  class GlobalFactory
    : public Factory<AbstractClass, Identifier, Compare, Creator, Destructor>,
      public coil::Singleton<GlobalFactory<AbstractClass,
                                           Identifier,
                                           Compare,
                                           Creator,
                                           Destructor> >
  {
  public:

  private:
    GlobalFactory(){}
    ~GlobalFactory(){}
    friend class Singleton<GlobalFactory>;
  };

}; // namespace coil
#endif // COIL_FACTORY_H
