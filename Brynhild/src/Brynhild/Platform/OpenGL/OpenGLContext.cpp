#include "PreCompiledHeader.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Brynhild {
  OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window)
  {
    BRYN_CORE_ASSERT(window, "Window for OGL Context is null!");
  }
  
  void OpenGLContext::Init() const
  {
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      BRYN_CORE_ERROR("Failed to initialize GLAD");
    }

    BRYN_CORE_INFO("OpenGL information:");
    BRYN_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    BRYN_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    BRYN_CORE_INFO("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
  }
  
  void OpenGLContext::SwapBuffers() const
  {
    glfwSwapBuffers(m_Window);
  }
}
