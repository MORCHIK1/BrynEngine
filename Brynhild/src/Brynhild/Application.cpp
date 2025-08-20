#include "PreCompiledHeader.h"
#include "Application.h"
#include "Brynhild/Input.h"
#include "Brynhild/KeyCode.h"

#include <glad/glad.h>


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

    float vertices[3 * 7] = {
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
       0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
       0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    uint32_t indices[3] = {
      0, 1, 2
    };

    BufferLayoutList layoutList = {
      { ShaderDataType::Float3 , "a_Position" },
      { ShaderDataType::Float4 , "a_Color" },
    };

    m_VAO.reset(VertexArray::Create(layoutList));
    m_VAO->Bind();

    m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
    m_VBO->Bind();

    m_EBO.reset(OGLElementBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t))); //We pass the count and not just the size, so we know how many indices there are and easily get the count
    m_EBO->Bind();

    m_VAO->EnableVertexAttrib();
  }

  Application::~Application()
  {
  }

  void Application::OnEvent(Event& event)
  {
    //We receive some event and create dispatcher with this event
    EventDispatcher dispatcher(event);
    //If we check this Event and it turns out to be WindowCloseEvent dispatcher calls OnWindowClosedEvent
    // 
    dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(Application::OnKeyPressedEvent));

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

  bool Application::OnKeyPressedEvent(KeyPressedEvent& event)
  {
    if (Input::IsKeyPressed(BRYN_KEY_ESCAPE)) {
      m_Running = false;
      return true;
    }
    return false;
  }

  void Application::Run() {
    while (m_Running) {
      glClearColor(0.2f, 0.2f, 0.2f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      m_VAO->Bind();

      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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