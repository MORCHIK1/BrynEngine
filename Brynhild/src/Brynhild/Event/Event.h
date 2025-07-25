#pragma once

#include <string> //PCH works, just IntelliSense says that there is an error. So include string is here for intellisense. Compiler will(at least should) ignore this line in compile time 
#include <functional> //same for this.
#include "Brynhild/Core.h"

namespace Brynhild {
  enum class EventType {
    None = 0,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
    WindowClose, WindowResize, WindowMoved, WindowLostFocus, WindowFocus,
    AppTick, AppUpdate, AppRender
  };

  enum class EventCategory {
    None = 0,
    EventCategoryKeyboard     = 1<<0,
    EventCategoryMouse        = 1<<1,
    EventCategoryApplication  = 1<<2,
    EventCategoryInput        = 1<<3,
    EventCategoryMouseButton  = 1<<4,
  };

  inline EventCategory operator|(EventCategory a, EventCategory b) {
    using UnderlyingType = std::underlying_type_t<EventCategory>;
    return static_cast<EventCategory>(static_cast<UnderlyingType>(a) | static_cast<UnderlyingType>(b));
  }

  inline EventCategory operator&(EventCategory a, EventCategory b) {
    using UnderlyingType = std::underlying_type_t<EventCategory>;
    return static_cast<EventCategory>(static_cast<UnderlyingType>(a) & static_cast<UnderlyingType>(b));
  }

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                               virtual EventType GetEventType() const override { return GetStaticType(); }\
                               virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual EventCategory GetCategoryFlags() const override { return category; } 

  class Event {
    friend class EventDispatcher;
  public:
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual EventCategory GetCategoryFlags() const = 0;
    virtual std::string ToString() const {
      return GetName();
    }

    inline bool isInCategory(EventCategory category) const{
      return (category & GetCategoryFlags()) != EventCategory::None; //Categories are set with left bitwise shift operation, so we are using AND(&) to find if it's in Category. 
      //New overloaded & returns EventCategory, so we have to compare it to EventCategory::None and not to 0
    }
  protected:
    bool m_Handled = false;
  };

  class EventDispatcher {
    template<typename T>
    using EventFn = std::function<bool(T&)>;

  public:
    EventDispatcher(Event& event) : m_Event(event) {}

    template<typename T>
    bool Dispatch(EventFn<T> func) { //The event function should be implemented in a respective class. E.g. WindowClosed function will be in WindowCloseEvent class
      if (m_Event.GetEventType() == T::GetStaticType()) {
        //(T*) is a cast to a certain event which we are sure to get thanks to our if statement
        BRYN_CORE_INFO("Event {} dispatch", m_Event.GetName())
        m_Event.m_Handled = func(*(T*)&m_Event);
        BRYN_CORE_INFO("Dispatcher of {0} status is {1}", m_Event.GetName(), m_Event.m_Handled)
        return true;
      }
      return false;
    }
  private:
    Event& m_Event;
  };
  inline std::ostream& operator<<(std::ostream& os, const Event& e)
  {
    return os << e.ToString();
  }
}