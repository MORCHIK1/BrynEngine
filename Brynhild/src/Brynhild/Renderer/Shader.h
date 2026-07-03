#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace Brynhild {
  class Shader
  {
  public:
    virtual ~Shader() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    // Uniform API
    virtual void SetInt(const std::string& name, int value) = 0;
    virtual void SetFloat(const std::string& name, float value) = 0;
    virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;
    virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;
    virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

    static std::shared_ptr<Shader> Create(const std::string& filepath);
  };
}
