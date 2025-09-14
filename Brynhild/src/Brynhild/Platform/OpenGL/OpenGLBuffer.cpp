#include "PreCompiledHeader.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Brynhild {
  static GLenum ShaderDataTypeToOGLType(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float:    { return GL_FLOAT; }
    case ShaderDataType::Float2:   { return GL_FLOAT; }
    case ShaderDataType::Float3:   { return GL_FLOAT; }
    case ShaderDataType::Float4:   { return GL_FLOAT; }
    case ShaderDataType::Float2x2: { return GL_FLOAT; }
    case ShaderDataType::Float3x3: { return GL_FLOAT; }
    case ShaderDataType::Float4x4: { return GL_FLOAT; }
    case ShaderDataType::Int:      { return GL_INT; }
    case ShaderDataType::Int2:     { return GL_INT; }
    case ShaderDataType::Int3:     { return GL_INT; }
    case ShaderDataType::Int4:     { return GL_INT; }
    }

    BRYN_CORE_ASSERT(false, "Type for OGLType doesn't exist!");
    return 0;
  }

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

  void OGLVertexBuffer::SetLayout(BufferLayoutList list)
  {
    m_LayoutList = list;
  }

  const BufferLayoutList& OGLVertexBuffer::GetLayout() const
  {
    return m_LayoutList;
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

  OGLVertexArray::OGLVertexArray()
  {
    glGenVertexArrays(1, &m_ArrayID);
  }
  OGLVertexArray::~OGLVertexArray()
  {
    glDeleteVertexArrays(1, &m_ArrayID);
  }
  void OGLVertexArray::Bind()
  {
    glBindVertexArray(m_ArrayID);
  }
  void OGLVertexArray::Unbind()
  {
    glBindVertexArray(0);
  }

  void OGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuf)
  {
    BRYN_CORE_ASSERT(vertexBuf->GetLayout().GetElements().size(), "The buffer layout list is empty!");

    glBindVertexArray(m_ArrayID);
    vertexBuf->Bind();

    const auto& layoutList = vertexBuf->GetLayout();

    for (const auto& layout : layoutList) {
      glEnableVertexAttribArray(m_AttribArray);
      glVertexAttribPointer(m_AttribArray, GetComponentCount(layout.DataType),
        ShaderDataTypeToOGLType(layout.DataType),
        layout.Normalized ? GL_TRUE : GL_FALSE,
        layoutList.GetStride(),
        (void*)layout.Offset);
      ++m_AttribArray;
    }

    m_VertexBufList.push_back(vertexBuf);
  }

  void OGLVertexArray::AddElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuf)
  {
    BRYN_CORE_ASSERT(elementBuf->GetCount(), "The element list is empty!");

    glBindVertexArray(m_ArrayID);
    elementBuf->Bind();

    m_ElementBuf = elementBuf;
  }

  const std::vector<std::shared_ptr<VertexBuffer>>& OGLVertexArray::GetVertexBuffer()
  {
    return m_VertexBufList;
  }

  const std::shared_ptr<ElementBuffer>& OGLVertexArray::GetElementBuffer()
  {
    return m_ElementBuf;
  }

  //--------------------------------UBO--------------------------------

  OGLUniformBuffer::OGLUniformBuffer(const std::vector<char>& constantBufferData, uint32_t layerIndex = 0) : m_Layout(layerIndex)
  {
    glGenBuffers(1, &m_UniformID);
    glBindBuffer(GL_UNIFORM_BUFFER, m_UniformID);
    glBufferData(GL_UNIFORM_BUFFER, constantBufferData.size(), constantBufferData.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, m_Layout, m_UniformID);
  }

  OGLUniformBuffer::~OGLUniformBuffer()
  {
    glDeleteBuffers(1, &m_UniformID);
  }

  void OGLUniformBuffer::Bind()
  {
    glBindBuffer(GL_UNIFORM_BUFFER, m_UniformID);
  }

  void OGLUniformBuffer::Unbind()
  {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }

  void OGLUniformBuffer::UpdateUBO(const std::vector<char>& constantBufferData)
  {
    if (m_UniformID == 0) {
      BRYN_CORE_ERROR("UBO WASN'T CREATED! ");
      return;
    }
    glBindBuffer(GL_UNIFORM_BUFFER, m_UniformID);

    glBufferSubData(GL_UNIFORM_BUFFER, 0, constantBufferData.size(), constantBufferData.data());

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }

}
