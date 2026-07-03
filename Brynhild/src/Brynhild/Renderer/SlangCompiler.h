#pragma once

#include <string>
#include <slang.h>
#include <slang-com-ptr.h>
#include <slang-com-helper.h>

namespace Brynhild {

  struct SlangCompiledGLSL {
    std::string vertexSource;
    std::string fragmentSource;
  };

  class SlangCompiler
  {
  public:
    static SlangCompiler& Get();

    SlangCompiledGLSL CompileToGLSL(const std::string& filepath,
      const std::string& vertexEntry = "vertexMain",
      const std::string& fragmentEntry = "fragmentMain");

  private:
    SlangCompiler();
    ~SlangCompiler() = default;

    SlangCompiler(const SlangCompiler&) = delete;
    SlangCompiler& operator=(const SlangCompiler&) = delete;

    Slang::ComPtr<slang::IGlobalSession> m_GlobalSession;
  };
}
