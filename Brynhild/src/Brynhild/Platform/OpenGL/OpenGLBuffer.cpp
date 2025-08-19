#include "PreCompiledHeader.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Brynhild {

  //--------------------------------VBO--------------------------------
  
  OGLVertexBuffer::OGLVertexBuffer(float* vertices, uint32_t size)
  {
    glGenBuffers(1, &m_VertexID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  }
  OGLVertexBuffer::~OGLVertexBuffer() {
    glDeleteBuffers(1, &m_VertexID);
  }

  void OGLVertexBuffer::Bind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
  }
  void OGLVertexBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  
  //--------------------------------EBO--------------------------------

  OGLElementBuffer::OGLElementBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
  {
    glGenBuffers(1, &m_ElementID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
  }

  OGLElementBuffer::~OGLElementBuffer() {
    glDeleteBuffers(1, &m_ElementID);
  }

  void OGLElementBuffer::Bind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementID);
  }
  void OGLElementBuffer::Unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  //--------------------------------VAO--------------------------------

  OGLVertexArray::OGLVertexArray(float* vertices, uint32_t count)
  {
    glGenVertexArrays(1, &m_ArrayID);
  }
  OGLVertexArray::~OGLVertexArray()
  {
  }
  void OGLVertexArray::Bind()
  {
  }
  void OGLVertexArray::Unbind()
  {
  }
}