#include "PreCompiledHeader.h"
#include "Shader.h"

#include "Brynhild/Renderer/Renderer.h"
#include "Brynhild/Platform/OpenGL/OpenGLShader.h"

namespace Brynhild {


  Shader::Shader() {
  }
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

    Slang::ComPtr<slang::IComponentType> linkedProgram;
    {
      Slang::ComPtr<slang::IBlob> diagnosticsBlob;
      SlangResult result = composedProgram->link(
        linkedProgram.writeRef(),
        diagnosticsBlob.writeRef());
    }

    Slang::ComPtr<slang::IBlob> VertexCodeBlob;
    Slang::ComPtr<slang::IBlob> FragmentCodeBlob;
    {
      Slang::ComPtr<slang::IBlob> diagnosticsBlob;
      // Get code for the first entry point (index 0, our vertex shader)
      SlangResult result = linkedProgram->getEntryPointCode(
        0, // entryPointIndex
        0, // targetIndex
        VertexCodeBlob.writeRef(),
        diagnosticsBlob.writeRef());

      // Get code for the second entry point (index 1, our fragment shader)
      result = linkedProgram->getEntryPointCode(
        1, // entryPointIndex
        0, // targetIndex
        FragmentCodeBlob.writeRef(),
        diagnosticsBlob.writeRef());

    }

    std::string vertexShaderSourceGLSL = static_cast<const char*>(VertexCodeBlob->getBufferPointer());
    std::string fragmentShaderSourceGLSL = static_cast<const char*>(FragmentCodeBlob->getBufferPointer());

    return { vertexShaderSourceGLSL, fragmentShaderSourceGLSL };
  }
}