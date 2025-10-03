#pragma once

#include <slang.h>
#include <slang-com-ptr.h>
#include <slang-com-helper.h>

namespace Brynhild {
  class Shader
  {
  public:
    Shader();
    virtual ~Shader() {};

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    static Shader* Create(const char* shaderName);
  private:
    static std::pair<std::string, std::string> CreateGLSLShader(std::string shaderName);
  private:
  };
}

