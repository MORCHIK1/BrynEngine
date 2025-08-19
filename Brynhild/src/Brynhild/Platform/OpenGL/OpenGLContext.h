#pragma once

#include "Brynhild/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Brynhild {
  class OpenGLContext : public GraphicsContext
  {
  public:
    OpenGLContext(GLFWwindow* window);

    virtual void Init() const override;
    virtual void SwapBuffers() const override;

  private:
    GLFWwindow* m_Window;
  };

}
