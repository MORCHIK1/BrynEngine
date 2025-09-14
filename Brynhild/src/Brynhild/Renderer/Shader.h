#pragma once

#include <slang.h>
#include <slang-com-ptr.h>
#include <slang-com-helper.h>

#include <iostream>

namespace Brynhild {
  class Shader
  {
  public:
    Shader();
    virtual ~Shader() {};

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    static Shader* Create(const char* shaderName);

    slang::ProgramLayout* getProgramLayout() { return m_ProgramLayout; }
  private:
    static std::pair<std::string, std::string> CreateGLSLShader(std::string shaderName);
    static Slang::ComPtr<slang::IComponentType> m_LinkedProgram;
    static slang::ProgramLayout* m_ProgramLayout;
  };


  class UniformBufferBuilder
  {
  public:
    UniformBufferBuilder(slang::ProgramLayout* programLayout, uint32_t bindingPoint)
    {
      if (!programLayout)
      {
        std::cerr << "UniformBufferBuilder Error: programLayout is null." << std::endl;
        return;
      }

      // --- Find the Constant Buffer (Parameter Block) by its binding point ---
      SlangInt paramCount = programLayout->getParameterCount();
      for (SlangInt i = 0; i < paramCount; ++i)
      {
        slang::VariableLayoutReflection* param = programLayout->getParameterByIndex(i);
        slang::TypeLayoutReflection* typeLayout = param->getTypeLayout();

        // Check if this parameter is a ConstantBuffer and matches our binding point
        if (typeLayout->getKind() == slang::TypeReflection::Kind::ConstantBuffer &&
          param->getBindingIndex() == bindingPoint)
        {
          // We found it! Get the layout for the struct INSIDE the ConstantBuffer<T>
          m_StructLayout = typeLayout->getElementTypeLayout();
          break; // Exit the loop
        }
      }

      if (m_StructLayout)
      {
        size_t bufferSize = m_StructLayout->getSize();
        if (bufferSize > 0)
        {
          m_cpuBuffer.resize(bufferSize);
          m_isValid = true;
          std::cout << "UniformBufferBuilder: Successfully found ConstantBuffer at binding " << bindingPoint
            << " with size " << bufferSize << " bytes." << std::endl;
        }
      }
      else
      {
        std::cerr << "UniformBufferBuilder Error: Could not find a ConstantBuffer at binding point "
          << bindingPoint << "." << std::endl;
      }
    }

    template <typename T>
    UniformBufferBuilder& setField(const char* fieldName, const T& value)
    {
      if (!m_isValid) return *this;

      // ==========================================================
      //                       CORRECTED CODE
      // ==========================================================
      // Manually iterate through the fields of the struct to find the one with the matching name.

      SlangUInt fieldCount = m_StructLayout->getFieldCount();
      for (SlangUInt i = 0; i < fieldCount; ++i)
      {
        slang::VariableLayoutReflection* field = m_StructLayout->getFieldByIndex(i);

        // Check if the name matches
        if (field && strcmp(field->getName(), fieldName) == 0)
        {
          // We found the correct field!
          size_t offset = field->getOffset();

          // Safety check
          if (offset + sizeof(T) > m_cpuBuffer.size())
          {
            std::cerr << "UniformBufferBuilder Error: Write for field '" << fieldName
              << "' would be out of bounds!" << std::endl;
          }
          else
          {
            memcpy(m_cpuBuffer.data() + offset, &value, sizeof(T));
          }

          // We're done, so we can exit the loop and the function.
          return *this;
        }
      }

      return *this;
    }

    const std::vector<char>& getBuffer() const { return m_cpuBuffer; }
    bool isValid() const { return m_isValid; }

  private:
    slang::TypeLayoutReflection* m_StructLayout = nullptr;
    std::vector<char> m_cpuBuffer;
    bool m_isValid = false;
  };

  slang::VariableLayoutReflection* findField(slang::TypeLayoutReflection* structLayout, const char* name);
}
