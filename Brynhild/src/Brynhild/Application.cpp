#include "PreCompiledHeader.h"
#include "Application.h"
#include "Brynhild/Input.h"
#include "Brynhild/KeyCode.h"
#include "Renderer/RenderManager.h"
#include "Renderer/Renderer.h"

#include <glad/glad.h>

#include <slang.h>

namespace Brynhild{
  Application* Application::s_Instance = nullptr;

  Application::Application()
  {
    BRYN_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));
    
    m_ImGuiLayer = new ImGuiLayer;

    PushOverlay(m_ImGuiLayer);
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
      if (Input::IsKeyPressed(BRYN_KEY_ESCAPE)) {
        m_Running = false;
      }

      for (Layer* layer : m_LayerStack) {
        layer->OnUpdate();
      }

      m_ImGuiLayer->Begin();
      for (Layer* layer : m_LayerStack) {
        layer->OnImGuiDraw();
      }
      m_ImGuiLayer->End();

      //auto [x, y] = Input::GetMousePos(); 
      //BRYN_CORE_TRACE("INPUT CHECK: {0} {1}", x, y);

      m_Window->OnUpdate();
    }
  }

  void Application::PushLayer(Layer* layer)
  {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
  }

  void Application::PushOverlay(Layer* layer)
  {
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
  }

}