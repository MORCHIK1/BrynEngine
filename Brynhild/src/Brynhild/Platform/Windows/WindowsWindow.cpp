#include <PreCompiledHeader.h>
#include "WindowsWindow.h"

namespace Brynhild {
  static bool s_GLFWInitialized = false;

  static void GLFWErrorCallback(int errorCode, const char* description) {
    BRYN_CORE_ERROR("GLFW Error code {0}, description {1}", errorCode, description);
  }

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

      BRYN_CORE_ASSERT(success, "COULD NOT INITIALIZE GLFW");
      glfwSetErrorCallback(GLFWErrorCallback);
      s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    //Setting GLFW callbacks for WindowEvents
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
      WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
    
      data.Width = width;
      data.Height = height;

      WindowResizeEvent event(height, width);
      data.EventCallback(event);
      });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
      WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

      WindowCloseEvent event;
      data.EventCallback(event);
      });

    //Setting GLFW callbacks for MouseEvents
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
      WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

      MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
      data.EventCallback(event);
      });


    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
      WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

      switch (action) {
      case GLFW_PRESS:
        {
          MouseButtonPressedEvent event(button);
          data.EventCallback(event);
          break;
        }
        case GLFW_RELEASE:
        {
          MouseButtonReleasedEvent event(button);
          data.EventCallback(event);
          break;
        }
      }
      });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
      WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

      MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
      data.EventCallback(event);
      });

    //Setting GLFW callbacks for KeyEvents
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

      switch (action) {
        case GLFW_PRESS:
        {
          KeyPressedEvent event(key, false);
          data.EventCallback(event);
          break;
        }
        case GLFW_RELEASE:
        {
          KeyReleasedEvent event(key);
          data.EventCallback(event);
          break;
        }
        case GLFW_REPEAT:
        {
          KeyPressedEvent event(key, true);
          data.EventCallback(event);
          break;
        }
      }

      });

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
