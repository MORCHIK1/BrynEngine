#pragma once

#include "Event.h"
#include <sstream>

namespace Brynhild {
  //Key pressed event, key released event
  class BRYN_API KeyEvent : public Event {
  public:
    inline int GetKeyCode() const{ return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput);
  protected:
    KeyEvent(int keyCode) : m_KeyCode(keyCode) {}

    int m_KeyCode;
  };

  class BRYN_API KeyPressedEvent : public KeyEvent {
  public:
    KeyPressedEvent(int keyCode, bool repeatCount) : m_RepeatCount(repeatCount), KeyEvent(keyCode){}

    inline bool GetRepeatCount() const { return m_RepeatCount; }

    std::string ToString() const override {
      std::stringstream ss;
      ss << "Key Pressed Event. Key pressed:" << m_KeyCode << "," << m_RepeatCount << "times";
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed);
  private:
    bool m_RepeatCount;
  };

  class BRYN_API KeyReleasedEvent : public KeyEvent {
  public:
    KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
    
    std::string ToString() const override {
      std::stringstream ss;
      ss << "Key Pressed Event. Key" << m_KeyCode;
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased);
  };

  class BRYN_API KeyTypedEvent : public KeyEvent {
  public:
    KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

    std::string ToString() const override {
      std::stringstream ss;
      ss << "Key Typed Event. Key: " << m_KeyCode;
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped);
  };
}