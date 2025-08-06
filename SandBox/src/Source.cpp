#include <Brynhild.h>

class ExampleLayer : public Brynhild::Layer{
public:
  ExampleLayer() : Layer("Example") {};

  void OnUpdate() override {
  }

  void OnEvent(Brynhild::Event& event) override {
  }
};

class Sandbox : public Brynhild::Application 
{
public:
  Sandbox() 
  {
    PushLayer(new ExampleLayer());
    PushOverlay(new Brynhild::ImGuiLayer());
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