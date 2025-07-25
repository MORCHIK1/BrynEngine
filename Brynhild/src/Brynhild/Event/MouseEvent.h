#pragma once

#include "Event.h"
#include <sstream>

namespace Brynhild {
  //MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled

  class BRYN_API MouseMovedEvent : public Event {
  public:
    MouseMovedEvent(float mouseX, float mouseY) : m_MouseX(mouseX), m_MouseY(mouseY) {}

    inline float GetX() const { return m_MouseX; }
    inline float GetY() const { return m_MouseY; }

    std::string ToString() const override {
      std::stringstream ss;
      ss << "MouseMovedEvent X: " << m_MouseX << " ,Y: " << m_MouseY;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved);
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);

  private:
    float m_MouseX, m_MouseY;
  };

  class BRYN_API MouseScrolledEvent : public Event {
  public:
    MouseScrolledEvent(float offsetX, float offsetY) : m_XOffset(offsetX), m_YOffset(offsetY) {}

    inline float GetXOffset() const { return m_XOffset; }
    inline float GetYOffset() const { return m_YOffset; }

    std::string ToString() const override {
      std::stringstream ss;
      ss << "MouseScrolledEvent X: " << m_XOffset << " ,Y: " << m_YOffset;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled);
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);

  private:
    float m_XOffset, m_YOffset;
  };

  class BRYN_API MouseButtonEvent : public Event {
  public:
    inline float GetMouseButton() const { return m_Button; }

    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);

  protected:
    MouseButtonEvent(int button) : m_Button(button) {}
    int m_Button;
  };

  class BRYN_API MouseButtonPressedEvent : public MouseButtonEvent {
  public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

    inline float GetMouseButton() const { return m_Button; }

    std::string ToString() const override {
      std::stringstream ss;
      ss << "MouseButtonPressedEvent X: " << m_Button;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed);
  };

  class BRYN_API MouseButtonReleasedEvent : public MouseButtonEvent {
  public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

    inline float GetMouseButton() const { return m_Button; }

    std::string ToString() const override {
      std::stringstream ss;
      ss << "MouseButtonReleasedEvent X: " << m_Button;
      return ss.str();
    }
    
    EVENT_CLASS_TYPE(MouseButtonReleased);
  };
}