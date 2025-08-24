#include "PreCompiledHeader.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

Brynhild::OpenGLShader::OpenGLShader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // link shaders
  m_ID = glCreateProgram();
  glAttachShader(m_ID, vertexShader);
  glAttachShader(m_ID, fragmentShader);
  glLinkProgram(m_ID);
  // check for linking errors
  glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Brynhild::OpenGLShader::~OpenGLShader()
{
  glDeleteProgram(m_ID);
}

void Brynhild::OpenGLShader::Bind()
{
  glUseProgram(m_ID);
}

void Brynhild::OpenGLShader::Unbind()
{
  glUseProgram(0);
}
