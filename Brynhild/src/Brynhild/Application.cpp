#include "PreCompiledHeader.h"
#include "Application.h"
#include "GLFW/glfw3.h"

namespace Brynhild{
  Application::Application()
  {
    m_Window = std::unique_ptr<Window>(Window::Create());
  }

  Application::~Application()
  {
  }

  void Application::Run() {
    WindowResizeEvent event(1280, 720);
    if (event.isInCategory(EventCategory::EventCategoryApplication)) {
      BRYN_CORE_CRITICAL(event)
    }

    EventDispatcher dispatch(event);
    
    dispatch.Dispatch<WindowResizeEvent>([](WindowResizeEvent& e) -> bool {
      BRYN_CORE_INFO("WindowResizeEvent handled!");
    
      BRYN_CORE_TRACE("New size: Width = {0}, Height = {1}", e.GetWidth(), e.GetHeight());
    
      return false;
      });

    while (m_Running) {
      m_Window->OnUpdate();

      glClearColor(0.2f, 0.2f, 0.2f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
  }
}