#include <Brynhild.h>

#include "imgui/imgui.h"

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
  };

  void OnUpdate() override {
    Brynhild::RenderManager::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.f });

    Brynhild::Renderer::BeginPlay();

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