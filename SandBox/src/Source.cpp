#include <Brynhild.h>

#include "imgui/imgui.h"

#include <slang.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Brynhild::Layer{
public:
  ExampleLayer() : Layer("Example") {
    m_VAO.reset(Brynhild::VertexArray::Create());
    BRYN_CORE_ASSERT(m_VAO, "VAO is null!");

    m_VAO->Bind();

    float vertices[3 * 3] = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f,  0.5f, 0.0f
    };

    Brynhild::BufferLayoutList layoutList = {
      { Brynhild::ShaderDataType::Float3 , "a_Position" },
    };

    std::shared_ptr<Brynhild::VertexBuffer> VBO = Brynhild::VertexBuffer::Create(vertices, std::size(vertices) * sizeof(float));
    BRYN_CORE_ASSERT(VBO, "VBO is null!");

    VBO->SetLayout(layoutList);
    m_VAO->AddVertexBuffer(VBO);

    uint32_t indices[3] = {
      0, 1, 2
    };

    std::shared_ptr<Brynhild::ElementBuffer> EBO = Brynhild::ElementBuffer::Create(indices, std::size(indices)); // We pass the count and not just the size, so we know how many indices there are and easily get the count
    
    m_VAO->AddElementBuffer(EBO);

    m_Shader.reset(Brynhild::Shader::Create("Shader"));

    Brynhild::UniformBufferBuilder initialBuilder(m_Shader->getProgramLayout(), 0);

    if (initialBuilder.isValid())
    {
      // The builder is now used like before
      FData myData;
      myData.a = 0.5f;
      myData.b = 42;

      initialBuilder.setField("a", myData.a) // Looks for a global param named "a" at binding 0
        .setField("b", myData.b); // Looks for a global param named "b" at binding 0

      // This part remains the same
    }
    m_UBO = Brynhild::UniformBuffer::Create(initialBuilder.getBuffer(), 0);
  };

  void OnUpdate() override {
    Brynhild::RenderManager::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.f });

    Brynhild::Renderer::BeginPlay();

    FData myData;
    myData.a = 0.5;
    myData.b = 0;

    // 2. Use the builder to prepare the GPU-formatted buffer
    Brynhild::UniformBufferBuilder builder(m_Shader->getProgramLayout(), 0);
    if (builder.isValid())
    {
      // Manually map fields from your C++ struct to the shader struct
      builder.setField("a", myData.a);
      builder.setField("b", myData.b);

      // 3. Get the final buffer and upload it
      m_UBO->UpdateUBO(builder.getBuffer()); // Your OpenGL function
    }

    Brynhild::Renderer::Submit(m_VAO, m_Shader);

    Brynhild::Renderer::EndPlay();
  }

  void OnImGuiDraw() override {
    ImGui::Begin("My sandbox app!");
    ImGui::Text("Great app!");
    ImGui::End();
  }

  void OnEvent(Brynhild::Event& event) override {
  }
private:
  std::shared_ptr<Brynhild::Shader> m_Shader;
  std::shared_ptr<Brynhild::VertexArray> m_VAO;
  std::shared_ptr<Brynhild::UniformBuffer> m_UBO;

  struct FData {
    float a;
    int   b;
  };
};

class Sandbox : public Brynhild::Application 
{
public:
  Sandbox() 
  {
    PushLayer(new ExampleLayer());
  }

  ~Sandbox() 
  {

  }
};

// This is the crucial part! The engine defines this function, but the CLIENT (Sandbox)
// is what implements it to return an instance of its own application.
Brynhild::Application* Brynhild::CreateApplication() 
{
  return new Sandbox();
}