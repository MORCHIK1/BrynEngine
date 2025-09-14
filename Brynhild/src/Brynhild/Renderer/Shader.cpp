#include "PreCompiledHeader.h"
#include "Shader.h"

#include "Brynhild/Renderer/Renderer.h"
#include "Brynhild/Platform/OpenGL/OpenGLShader.h"

Slang::ComPtr<slang::IComponentType> Brynhild::Shader::m_LinkedProgram;
slang::ProgramLayout* Brynhild::Shader::m_ProgramLayout = nullptr;

namespace Brynhild {
  Shader::Shader() {}
  Shader* Shader::Create(const char* shaderName)
  {
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::API::None:
      BRYN_CORE_ERROR("No shader for API None!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      BRYN_CORE_INFO("Returning GLSL shader...");
      auto [vertex, fragment] = CreateGLSLShader(shaderName);
      return new OpenGLShader(vertex.c_str(), fragment.c_str());
    }

    BRYN_CORE_ASSERT(false, "Wrong RendererAPI for Shader!");
    return nullptr;
  }

  std::pair<std::string, std::string> Shader::CreateGLSLShader(std::string shaderName)
  {
    Slang::ComPtr<slang::IGlobalSession> globalSession;
    createGlobalSession(globalSession.writeRef());

    slang::SessionDesc sessionDesc = {};

    slang::TargetDesc targetDesc = {};
    targetDesc.format = SLANG_GLSL;
    targetDesc.profile = globalSession->findProfile("glsl_460");

    sessionDesc.targets = &targetDesc;
    sessionDesc.targetCount = 1;

    Slang::ComPtr<slang::ISession> session;
    globalSession->createSession(sessionDesc, session.writeRef());

    Slang::ComPtr<slang::IModule> slangModule;
    {
      Slang::ComPtr<slang::IBlob> diagnosticsBlob;
      const char* moduleName = shaderName.c_str();

      std::string shaderPath = "assets/shaders/" + shaderName + ".slang";
      const char* modulePath = shaderPath.c_str();

      slangModule = session->loadModule(modulePath, diagnosticsBlob.writeRef());

      if (diagnosticsBlob) {
        BRYN_CORE_ERROR("Slang Diagnostics: {0}", (const char*)diagnosticsBlob->getBufferPointer());
      }
      
      BRYN_CORE_ASSERT(slangModule, "Error loading module!");
    }

    Slang::ComPtr<slang::IEntryPoint> VertexEntryPoint;
    {
      Slang::ComPtr<slang::IBlob> diagnosticsBlob;
      slangModule->findEntryPointByName("vertexMain", VertexEntryPoint.writeRef());
      BRYN_CORE_ASSERT(VertexEntryPoint, "Error getting entry point for Vertex");
    }

    Slang::ComPtr<slang::IEntryPoint> FragmentEntryPoint;
    {
      Slang::ComPtr<slang::IBlob> diagnosticsBlob;
      slangModule->findEntryPointByName("fragmentMain", FragmentEntryPoint.writeRef());
      BRYN_CORE_ASSERT(FragmentEntryPoint, "Error getting entry point for Fragment");
    }

    std::array<slang::IComponentType*, 3> componentTypes =
    {
        slangModule,
        VertexEntryPoint,
        FragmentEntryPoint
    };

    Slang::ComPtr<slang::IComponentType> composedProgram;
    {
      Slang::ComPtr<slang::IBlob> diagnosticsBlob;
      SlangResult result = session->createCompositeComponentType(
        componentTypes.data(),
        componentTypes.size(),
        composedProgram.writeRef(),
        diagnosticsBlob.writeRef());
    }
    {
      Slang::ComPtr<slang::IBlob> diagnosticsBlob;
      SlangResult result = composedProgram->link(
        m_LinkedProgram.writeRef(),
        diagnosticsBlob.writeRef());
    }

    m_ProgramLayout = m_LinkedProgram->getLayout();

    Slang::ComPtr<slang::IBlob> VertexCodeBlob;
    Slang::ComPtr<slang::IBlob> FragmentCodeBlob;
    {
      Slang::ComPtr<slang::IBlob> diagnosticsBlob;
      // Get code for the first entry point (index 0, our vertex shader)
      SlangResult result = m_LinkedProgram->getEntryPointCode(
        0, // entryPointIndex
        0, // targetIndex
        VertexCodeBlob.writeRef(),
        diagnosticsBlob.writeRef());

      // Get code for the second entry point (index 1, our fragment shader)
      result = m_LinkedProgram->getEntryPointCode(
        1, // entryPointIndex
        0, // targetIndex
        FragmentCodeBlob.writeRef(),
        diagnosticsBlob.writeRef());
    }

    std::string vertexShaderSourceGLSL = static_cast<const char*>(VertexCodeBlob->getBufferPointer());
    std::string fragmentShaderSourceGLSL = static_cast<const char*>(FragmentCodeBlob->getBufferPointer());

    return { vertexShaderSourceGLSL, fragmentShaderSourceGLSL };
  }

  slang::VariableLayoutReflection* findGlobalParameter(slang::ProgramLayout* programLayout, const char* name)
  {
    SlangInt paramCount = programLayout->getParameterCount();

    for (SlangInt i = 0; i < paramCount; ++i)
    {
      slang::VariableLayoutReflection* param = programLayout->getParameterByIndex(i);
      if (strcmp(param->getName(), name) == 0)
      {
        return param;
      }
    }
    return nullptr;
  }

  slang::VariableLayoutReflection* findField(slang::TypeLayoutReflection* structLayout, const char* name)
  {
    SlangUInt fieldCount = structLayout->getFieldCount();
    for (SlangUInt i = 0; i < fieldCount; ++i)
    {
      slang::VariableLayoutReflection* field = structLayout->getFieldByIndex(i);
      if (strcmp(field->getName(), name) == 0)
      {
        return field;
      }
    }
    return nullptr;
  }

  // --- Variadic Template Implementation ---

  // This is the recursive "worker" function.
  // Base case: When there are no more arguments to process, we stop.
  void setBufferFields(
    char* cpuBufferData,
    slang::TypeLayoutReflection* structLayout)
  {
    // All done!
  }

  // Recursive step: Process one name-value pair and recurse on the rest.
  template<typename T, typename... Rest>
  void setBufferFields(
    char* cpuBufferData,
    slang::TypeLayoutReflection* structLayout,
    const char* fieldName,
    const T& value,
    Rest... rest)
  {
    // Find the field with the given name inside the struct.
    slang::VariableLayoutReflection* fieldLayout = findField(structLayout, fieldName);

    if (fieldLayout)
    {
      // Get the byte offset where this field's data should be placed.
      size_t offset = fieldLayout->getOffset();

      Optional but recommended: Check if the size matches.
      size_t requiredSize = fieldLayout->getTypeLayout()->getSize();
      if (sizeof(T) != requiredSize) {
          std::cerr << "Warning: Size mismatch for field '" << fieldName << "'. "
                    << "Provided: " << sizeof(T) << ", Shader expects: " << requiredSize << std::endl;
      }

      // Copy the value's bytes to the correct position in the buffer.
      memcpy(cpuBufferData + offset, &value, sizeof(T));
    }
    else
    {
      // It's good practice to warn if a field name wasn't found.
      std::cerr << "Warning: Field '" << fieldName << "' not found in constant buffer struct." << std::endl;
    }

    // Recursively call the function with the remaining arguments.
    setBufferFields(cpuBufferData, structLayout, rest...);
  }

}