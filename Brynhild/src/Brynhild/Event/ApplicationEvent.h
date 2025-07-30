#pragma once

#include "Event.h"
#include <sstream>

namespace Brynhild {
  //WINDOW EVENT CLASSES
  //Existing Events for Window: WindowClose, WindowResize, WindowLostFocus, WindowMoved, WindowFocus
  class BRYN_API WindowCloseEvent : public Event {
  public:
    WindowCloseEvent(){}

    std::string ToString() const override {
      std::stringstream ss;
      ss << "WindowCloseEvent";
      return ss.str();
    }

    EVENT_CLASS_TYPE(WindowClose);
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
  };

  class BRYN_API WindowResizeEvent : public Event {
  public:
    WindowResizeEvent(unsigned int height, unsigned int width) : m_Height(height), m_Width(width) {}

    inline unsigned int GetHeight() const { return m_Height; }
    inline unsigned int GetWidth() const { return m_Width; }

    std::string ToString() const override {
      std::stringstream ss;
      ss << "WindowResizeEvent Height: " << m_Height << ", Width: "<< m_Width;
      return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
  private:
    unsigned int m_Height, m_Width;
  };

  class BRYN_API WindowMovedEvent : public Event {
  public:
    WindowMovedEvent() {}

    std::string ToString() const override {
      std::stringstream ss;
      ss << "WindowMovedEvent";
      return ss.str();
    }

    EVENT_CLASS_TYPE(WindowMoved);
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
  };

  class BRYN_API WindowLostFocusEvent : public Event {
  public:
    WindowLostFocusEvent() {}

    std::string ToString() const override {
      std::stringstream ss;
      ss << "WindowLostFocus";
      return ss.str();
    }

    EVENT_CLASS_TYPE(WindowLostFocus);
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
  };

  class BRYN_API WindowFocusEvent : public Event {
  public:
    WindowFocusEvent() {}

    std::string ToString() const override {
      std::stringstream ss;
      ss << "WindowFocusEvent";
      return ss.str();
    }

    EVENT_CLASS_TYPE(WindowFocus);
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
  };

  //APP EVENT CLASSES
  
  class BRYN_API AppTickEvent : public Event {
  public:
    AppTickEvent() {}

    std::string ToString() const override {
      std::stringstream ss;
      ss << "AppTickEvent";
      return ss.str();
    }

    EVENT_CLASS_TYPE(AppTick);
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
  };


  class BRYN_API AppRenderEvent : public Event {
  public:
    AppRenderEvent() {}

    std::string ToString() const override {
      std::stringstream ss;
      ss << "AppRender";
      return ss.str();
    }

    EVENT_CLASS_TYPE(AppRender);
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
  };

  class BRYN_API AppUpdateEvent : public Event {
  public:
    AppUpdateEvent() {}

    std::string ToString() const override {
      std::stringstream ss;
      ss << "AppUpdateEvent";
      return ss.str();
    }

    EVENT_CLASS_TYPE(AppUpdate);
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
  };
  

}