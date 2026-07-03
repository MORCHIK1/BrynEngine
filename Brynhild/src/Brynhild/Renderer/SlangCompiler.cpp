#include "PreCompiledHeader.h"
#include "SlangCompiler.h"

#include <array>

namespace Brynhild {

  SlangCompiler::SlangCompiler()
  {
    SlangResult result = createGlobalSession(m_GlobalSession.writeRef());
    BRYN_CORE_ASSERT(SLANG_SUCCEEDED(result) && m_GlobalSession, "Failed to create Slang global session!");
    BRYN_CORE_INFO("Slang global session created successfully.");
  }

  SlangCompiler& SlangCompiler::Get()
  {
    static SlangCompiler instance;
    return instance;
  }

  SlangCompiledGLSL SlangCompiler::CompileToGLSL(const std::string& filepath,
    const std::string& vertexEntry,
    const std::string& fragmentEntry)
  {
    // --- Session setup (reuses m_GlobalSession) ---
    slang::SessionDesc sessionDesc = {};

    slang::TargetDesc targetDesc = {};
    targetDesc.format = SLANG_GLSL;
    targetDesc.profile = m_GlobalSession->findProfile("glsl_460");

    sessionDesc.targets = &targetDesc;
    sessionDesc.targetCount = 1;

    Slang::ComPtr<slang::ISession> session;
    m_GlobalSession->createSession(sessionDesc, session.writeRef());
    BRYN_CORE_ASSERT(session, "Failed to create Slang session!");

    // --- Load module ---
    Slang::ComPtr<slang::IModule> slangModule;
    {
      Slang::ComPtr<slang::IBlob> diagnosticsBlob;
      slangModule = session->loadModule(filepath.c_str(), diagnosticsBlob.writeRef());

      if (diagnosticsBlob) {
        BRYN_CORE_ERROR("Slang load diagnostics: {0}",
          (const char*)diagnosticsBlob->getBufferPointer());
      }
      BRYN_CORE_ASSERT(slangModule, "Failed to load Slang module: {0}", filepath);
    }

    // --- Find entry points ---
    Slang::ComPtr<slang::IEntryPoint> vertexEntryPoint;
    slangModule->findEntryPointByName(vertexEntry.c_str(), vertexEntryPoint.writeRef());
    BRYN_CORE_ASSERT(vertexEntryPoint, "Failed to find vertex entry point: {0}", vertexEntry);

    Slang::ComPtr<slang::IEntryPoint> fragmentEntryPoint;
    slangModule->findEntryPointByName(fragmentEntry.c_str(), fragmentEntryPoint.writeRef());
    BRYN_CORE_ASSERT(fragmentEntryPoint, "Failed to find fragment entry point: {0}", fragmentEntry);

    // --- Compose ---
    std::array<slang::IComponentType*, 3> componentTypes = {
        slangModule,
        vertexEntryPoint,
        fragmentEntryPoint
    };

    Slang::ComPtr<slang::IComponentType> composedProgram;
    {
      Slang::ComPtr<slang::IBlob> diagnosticsBlob;
      SlangResult result = session->createCompositeComponentType(
        componentTypes.data(),
        componentTypes.size(),
        composedProgram.writeRef(),
        diagnosticsBlob.writeRef());

      if (diagnosticsBlob) {
        BRYN_CORE_ERROR("Slang compose diagnostics: {0}",
          (const char*)diagnosticsBlob->getBufferPointer());
      }
      BRYN_CORE_ASSERT(SLANG_SUCCEEDED(result) && composedProgram,
        "Failed to compose Slang program!");
    }

    // --- Link ---
    Slang::ComPtr<slang::IComponentType> linkedProgram;
    {
      Slang::ComPtr<slang::IBlob> diagnosticsBlob;
      SlangResult result = composedProgram->link(
        linkedProgram.writeRef(),
        diagnosticsBlob.writeRef());

      if (diagnosticsBlob) {
        BRYN_CORE_ERROR("Slang link diagnostics: {0}",
          (const char*)diagnosticsBlob->getBufferPointer());
      }
      BRYN_CORE_ASSERT(SLANG_SUCCEEDED(result) && linkedProgram,
        "Failed to link Slang program!");
    }

    // --- Extract GLSL code ---
    Slang::ComPtr<slang::IBlob> vertexCodeBlob;
    Slang::ComPtr<slang::IBlob> fragmentCodeBlob;
    {
      Slang::ComPtr<slang::IBlob> diagnosticsBlob;

      SlangResult result = linkedProgram->getEntryPointCode(
        0, 0, vertexCodeBlob.writeRef(), diagnosticsBlob.writeRef());

      if (diagnosticsBlob) {
        BRYN_CORE_ERROR("Slang vertex codegen diagnostics: {0}",
          (const char*)diagnosticsBlob->getBufferPointer());
      }
      BRYN_CORE_ASSERT(SLANG_SUCCEEDED(result) && vertexCodeBlob,
        "Failed to get vertex shader code!");

      result = linkedProgram->getEntryPointCode(
        1, 0, fragmentCodeBlob.writeRef(), diagnosticsBlob.writeRef());

      if (diagnosticsBlob) {
        BRYN_CORE_ERROR("Slang fragment codegen diagnostics: {0}",
          (const char*)diagnosticsBlob->getBufferPointer());
      }
      BRYN_CORE_ASSERT(SLANG_SUCCEEDED(result) && fragmentCodeBlob,
        "Failed to get fragment shader code!");
    }

    SlangCompiledGLSL output;
    output.vertexSource = static_cast<const char*>(vertexCodeBlob->getBufferPointer());
    output.fragmentSource = static_cast<const char*>(fragmentCodeBlob->getBufferPointer());

    BRYN_CORE_INFO("Successfully compiled Slang shader: {0}", filepath);

    return output;
  }
}
