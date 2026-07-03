#pragma once

#include "Brynhild/Renderer/Shader.h"

namespace Brynhild {
  class OpenGLShader : public Shader
  {
  public:
    explicit OpenGLShader(const std::string& filepath);
    ~OpenGLShader();

    void Bind() override;
    void Unbind() override;

    void SetInt(const std::string& name, int value) override;
    void SetFloat(const std::string& name, float value) override;
    void SetVec3(const std::string& name, const glm::vec3& value) override;
    void SetVec4(const std::string& name, const glm::vec4& value) override;
    void SetMat4(const std::string& name, const glm::mat4& value) override;

  private:
    void CompileGLProgram(const std::string& vertexSource, const std::string& fragmentSource);
    int GetUniformLocation(const std::string& name);

    unsigned int m_ID = 0;
  };
}
