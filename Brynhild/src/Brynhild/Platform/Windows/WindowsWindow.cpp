#include <PreCompiledHeader.h>
#include "WindowsWindow.h"

namespace Brynhild {
  static bool s_GLFWInitialized = false;

  Window* Window::Create(const WindowProps& props) {
    return new WindowsWindow(props);
  }
  
  WindowsWindow::WindowsWindow(const WindowProps& props)
  {
    Init(props);
  }

  void WindowsWindow::Init(const WindowProps& props)
  {
    m_Data.Title = props.Title;
    m_Data.Height = props.Height;
    m_Data.Width = props.Width;
    
    BRYN_CORE_INFO("Creating Window {0} of size ({1} {2})", m_Data.Title, m_Data.Height, m_Data.Width)
    
    if (!s_GLFWInitialized) {
      int success = glfwInit();
      std::cout << success;

      BRYN_CORE_ASSERT(success, "COULD NOT INITIALIZE GLFW")

      s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);
  }

  void WindowsWindow::Shutdown()
  {
    glfwDestroyWindow(m_Window);
  }

  WindowsWindow::~WindowsWindow()
  {
    Shutdown();
  }

  void WindowsWindow::OnUpdate()
  {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
  }

  void WindowsWindow::SetVSync(bool enabled)
  {
    if (enabled) {
      glfwSwapInterval(1);
    }
    else {
      glfwSwapInterval(0);
    }
    m_Data.VSync = enabled;
  }
}
