#pragma once

#include "Core.h"
#include "Brynhild/Event/ApplicationEvent.h"
#include "Brynhild/Event/KeyEvent.h"
#include "Brynhild/LayerStack.h"
#include "Event/EventLog.h"
#include "ImGui/ImGuiLayer.h"
#include "Brynhild/Platform/OpenGL/OpenGLBuffer.h"
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

    inline Window& GetWindow() { return *m_Window; }

    inline static Application& Get() { return *s_Instance; }
  private:
    bool OnWindowClosedEvent(WindowCloseEvent& event);
    bool OnKeyPressedEvent(KeyPressedEvent& event);

    std::unique_ptr<Window> m_Window;

    std::unique_ptr<VertexArray> m_VAO;

    ImGuiLayer* m_ImGuiLayer;
    bool m_Running = true;
    LayerStack m_LayerStack;

    static Application* s_Instance;
  };

  //Will be defined in client(sandbox)
  Application* CreateApplication();
}