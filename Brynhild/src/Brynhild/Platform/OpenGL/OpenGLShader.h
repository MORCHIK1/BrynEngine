#pragma once

#include "Brynhild/Renderer/Shader.h"

namespace Brynhild {
  class OpenGLShader : public Shader
  {
  public:
    OpenGLShader(const char* vertexShader, const char* fragmentShader);
    ~OpenGLShader();

    void Bind() override;
    void Unbind() override;
  private:
    unsigned int m_ID;
  };
}

