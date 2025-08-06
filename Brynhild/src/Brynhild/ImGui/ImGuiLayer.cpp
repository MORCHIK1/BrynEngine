#include "PreCompiledHeader.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Brynhild/OpenGL/imguiOpenGL.h"
#include "Brynhild/OpenGL/imguiGLFW.h"
#include "Brynhild/Application.h"

#include <GLFW/glfw3.h>

namespace Brynhild{
  ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
  {
  }
  ImGuiLayer::~ImGuiLayer()
  {
  }
  void ImGuiLayer::OnAttach()
  {
    ImGui::CreateContext();
    ImGui::StyleColorsClassic();

    ImGuiIO& IO = ImGui::GetIO();

    IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 

    Application& app = Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

    ImGui_ImplOpenGL3_Init("#version 460");
    ImGui_ImplGlfw_InitForOpenGL(window, true);
  }

  void ImGuiLayer::OnDetach()
  {
  }
  void ImGuiLayer::OnUpdate()
  {
    ImGuiIO& IO = ImGui::GetIO();
    Application& app = Application::Get();
    IO.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    float time = static_cast<float>(glfwGetTime());
    IO.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.f / 60.f);
    m_Time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
  void ImGuiLayer::OnEvent(Event& event)
  {
    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(ImGuiLayer::OnKeyPressedEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT(ImGuiLayer::OnKeyReleasedEvent));
    dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT(ImGuiLayer::OnMouseButtonPressedEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT(ImGuiLayer::OnMouseButtonReleasedEvent));
    dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT(ImGuiLayer::OnMouseMovedEvent));
    dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT(ImGuiLayer::OnMouseScrolledEvent));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(ImGuiLayer::OnWindowResizeEvent));
  }


  bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& event)
  {
    ImGuiIO& IO = ImGui::GetIO();
    IO.KeyDa

    return false;
  }
  bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event)
  {
    return false;
  }
  bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
  {
    ImGuiIO& IO = ImGui::GetIO();
    IO.MouseDown[event.GetMouseButton()] = true;

    return false;
  }
  bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
  {
    ImGuiIO& IO = ImGui::GetIO();
    IO.MouseDown[event.GetMouseButton()] = true;

    return false;
  }
  bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& event)
  {
    ImGuiIO& IO = ImGui::GetIO();
    IO.MousePos = ImVec2(event.GetX(), event.GetY());

    return false;
  }
  bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event)
  {
    ImGuiIO& IO = ImGui::GetIO();
    IO.MouseWheelH += event.GetXOffset();
    IO.MouseWheel += event.GetYOffset();

    return false;
  }
  bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
  {
    ImGuiIO& IO = ImGui::GetIO();

    IO.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
    IO.DisplayFramebufferScale = ImVec2(1.f, 1.f);

    glViewport(0, 0, event.GetWidth(), event.GetHeight());

    return false;
  }
}