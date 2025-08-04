#include "PreCompiledHeader.h"
#include "Application.h"
#include "GLFW/glfw3.h"

namespace Brynhild{
#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

  Application::Application()
  {
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));
  }

  Application::~Application()
  {
  }

  void Application::OnEvent(Event& event)
  {
    //We receive some event and create dispatcher with this event
    EventDispatcher dispatcher(event);
    //If we check this Event and it turns out to be WindowCloseEvent dispatcher calls OnWindowClosedEvent
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClosedEvent));

    BRYN_CORE_INFO("Application OnEvent: {0}", event);

    for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
      (*it)->OnEvent(event);
      if (event.handled)
        break;
    }
  }

  bool Application::OnWindowClosedEvent(WindowCloseEvent& event)
  {
    m_Running = false;
    return true;
  }

  void Application::Run() {
    while (m_Running) {
      glClearColor(0.2f, 0.2f, 0.2f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      for (Layer* layer : m_LayerStack) {
        layer->OnUpdate();
      }

      m_Window->OnUpdate();
    }
  }

  void Application::PushLayer(Layer* layer)
  {
    m_LayerStack.PushLayer(layer);
  }

  void Application::PushOverlay(Layer* layer)
  {
    m_LayerStack.PushOverlay(layer);
  }

}