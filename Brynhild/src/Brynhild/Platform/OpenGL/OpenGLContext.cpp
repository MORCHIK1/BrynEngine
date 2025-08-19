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
  }
  
  void OpenGLContext::SwapBuffers() const
  {
    glfwSwapBuffers(m_Window);
  }
}
