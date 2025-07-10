#include <Brynhild.h>

class Sandbox : public Brynhild::Application 
{
public:
  Sandbox() 
  {

  }

  ~Sandbox() 
  {

  }
};

Brynhild::Application* Brynhild::CreateApplication() 
{
  return new Sandbox();
}