#pragma once

namespace Brynhild {
  //Should be later moved to respective Shader file
  //-----------------------------------------------
  enum class ShaderDataType {
    None = 0,
    Float, Float2, Float3, Float4,
    Int, Int2, Int3, Int4,
    Float2x2, Float3x3, Float4x4
  };

  static uint32_t ShaderDataTypeSize(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float:    return sizeof(float);
    case ShaderDataType::Float2:   return sizeof(float) * 2;
    case ShaderDataType::Float3:   return sizeof(float) * 3;
    case ShaderDataType::Float4:   return sizeof(float) * 4;
    case ShaderDataType::Int:      return sizeof(int);
    case ShaderDataType::Int2:     return sizeof(int) * 2;
    case ShaderDataType::Int3:     return sizeof(int) * 3;
    case ShaderDataType::Int4:     return sizeof(int) * 4;
    case ShaderDataType::Float2x2: return sizeof(float) * 2 * 2;
    case ShaderDataType::Float3x3: return sizeof(float) * 3 * 3;
    case ShaderDataType::Float4x4: return sizeof(float) * 4 * 4;
    }

    BRYN_CORE_ASSERT(false, "Type for Stride doesn't exist!");
    return 0;
  }


  static uint32_t GetComponentCount(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float:    return 1;
    case ShaderDataType::Float2:   return 2;
    case ShaderDataType::Float3:   return 3;
    case ShaderDataType::Float4:   return 4;
    case ShaderDataType::Int:      return 1;
    case ShaderDataType::Int2:     return 2;
    case ShaderDataType::Int3:     return 3;
    case ShaderDataType::Int4:     return 4;
    case ShaderDataType::Float2x2: return 2 * 2;
    case ShaderDataType::Float3x3: return 3 * 3;
    case ShaderDataType::Float4x4: return 4 * 4;
    }

    BRYN_CORE_ASSERT(false, "Type for Component Count doesn't exist!");
    return 0;
  }

  //-----------------------------------------------

  struct BufferLayoutElement {
    ShaderDataType DataType;
    std::string Name;
    uint32_t ComponentCount;
    uint32_t Offset;
    bool Normalized;

    BufferLayoutElement() {};

    BufferLayoutElement(ShaderDataType type, std::string name, bool normalized = false) :
      DataType(type), Name(name), ComponentCount(GetComponentCount(type)), Offset(0), Normalized(normalized)
    {}
  };

  class BufferLayoutList {
  public:
    BufferLayoutList() {};

    BufferLayoutList(const std::initializer_list<BufferLayoutElement>& layoutElements) : m_LayoutElements(layoutElements) {
      CalculateStrideAndOffset();
    };

    std::initializer_list<BufferLayoutElement>::iterator begin() { return m_LayoutElements.begin(); }
    std::initializer_list<BufferLayoutElement>::iterator end() { return m_LayoutElements.end(); }

    inline uint32_t GetStride() const { return m_Stride; }

  private:
    void CalculateStrideAndOffset();

    uint32_t m_Stride;
    std::initializer_list<BufferLayoutElement> m_LayoutElements;
  };

  class VertexBuffer
  {
  public:
    virtual ~VertexBuffer() {};

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    
    static VertexBuffer* Create(float* vertices, uint32_t size);
  };

  class VertexArray
  {
  public:
    virtual ~VertexArray() {};

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetLayout(BufferLayoutList list) = 0;
    virtual void EnableVertexAttrib() = 0;

    static VertexArray* Create(BufferLayoutList list);
  };

  class ElementBuffer
  {
  public:
    virtual ~ElementBuffer() {};

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual uint32_t GetCount() = 0; //Get count of how many indices there are

    static ElementBuffer* Create(uint32_t* indices, uint32_t size);
  };

}

