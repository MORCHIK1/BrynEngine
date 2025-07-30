#pragma once

#include "Core.h"
#include "Brynhild/Event/ApplicationEvent.h"
#include "Event/EventLog.h"
#include "Window.h"

namespace Brynhild 
{
  class BRYN_API Application
  {
  public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event& event);
  private:
    bool OnWindowClosedEvent(WindowCloseEvent& event);

    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
  };

  //Will be defined in client(sandbox)
  Application* CreateApplication();
}