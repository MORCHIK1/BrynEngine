#pragma once

#include "Core.h"
#include "Brynhild/Event/ApplicationEvent.h"
#include "Brynhild/LayerStack.h"
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

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    
    void OnEvent(Event& event);
  private:
    bool OnWindowClosedEvent(WindowCloseEvent& event);

    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
    LayerStack m_LayerStack;
  };

  //Will be defined in client(sandbox)
  Application* CreateApplication();
}