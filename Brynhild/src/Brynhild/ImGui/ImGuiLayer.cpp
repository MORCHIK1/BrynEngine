#include "PreCompiledHeader.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Brynhild/Application.h"

#include <GLFW/glfw3.h>

namespace Brynhild {
  ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
  {
  }
  ImGuiLayer::~ImGuiLayer()
  {
  }
  void ImGuiLayer::OnAttach()
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsClassic();

    ImGuiIO& IO = ImGui::GetIO(); 
    (void)IO;

    IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    IO.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGuiStyle& style = ImGui::GetStyle();
    if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      style.WindowRounding = 0.f;
      style.Colors[ImGuiCol_WindowBg].w = 1.f;
    }

    Application& app = Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

    ImGui_ImplOpenGL3_Init("#version 460");
    ImGui_ImplGlfw_InitForOpenGL(window, true);
  }

  void ImGuiLayer::OnDetach()
  {
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    
  }

  void ImGuiLayer::OnImGuiDraw()
  {
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
  }

  void ImGuiLayer::Begin()
  {
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
  }

  void ImGuiLayer::End()
  {
    ImGuiIO& IO = ImGui::GetIO();

    Application& app = Application::Get();
    IO.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }
  }
}