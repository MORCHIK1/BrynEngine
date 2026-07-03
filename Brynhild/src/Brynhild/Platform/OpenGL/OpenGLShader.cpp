#include "PreCompiledHeader.h"
#include "OpenGLShader.h"

#include "Brynhild/Renderer/SlangCompiler.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Brynhild {

  OpenGLShader::OpenGLShader(const std::string& filepath)
  {
    auto compiled = SlangCompiler::Get().CompileToGLSL(filepath);
    CompileGLProgram(compiled.vertexSource, compiled.fragmentSource);
  }

  void OpenGLShader::CompileGLProgram(const std::string& vertexSource, const std::string& fragmentSource)
  {
    const char* vertexSrc = vertexSource.c_str();
    const char* fragmentSrc = fragmentSource.c_str();

    // --- Compile vertex shader ---
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrc, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      BRYN_CORE_ERROR("SHADER::VERTEX::COMPILATION_FAILED: {0}", infoLog);
    }

    // --- Compile fragment shader ---
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      BRYN_CORE_ERROR("SHADER::FRAGMENT::COMPILATION_FAILED: {0}", infoLog);
    }

    // --- Link shader program ---
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glLinkProgram(m_ID);

    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) 
    {
      glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
      BRYN_CORE_ERROR("SHADER::PROGRAM::LINKING_FAILED: {0}", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
  }

  OpenGLShader::~OpenGLShader()
  {
    glDeleteProgram(m_ID);
  }

  void OpenGLShader::Bind()
  {
    glUseProgram(m_ID);
  }

  void OpenGLShader::Unbind()
  {
    glUseProgram(0);
  }

  // --- Uniform setters ---

  int OpenGLShader::GetUniformLocation(const std::string& name)
  {
    int location = glGetUniformLocation(m_ID, name.c_str());
    if (location == -1) 
    {
      BRYN_CORE_WARN("Uniform '{0}' not found in shader program!", name);
    }
    return location;
  }

  void OpenGLShader::SetInt(const std::string& name, int value)
  {
    glUniform1i(GetUniformLocation(name), value);
  }

  void OpenGLShader::SetFloat(const std::string& name, float value)
  {
    glUniform1f(GetUniformLocation(name), value);
  }

  void OpenGLShader::SetVec3(const std::string& name, const glm::vec3& value)
  {
    glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
  }

  void OpenGLShader::SetVec4(const std::string& name, const glm::vec4& value)
  {
    glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
  }

  void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
  {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
  }
}
