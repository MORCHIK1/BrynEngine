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

// This is the crucial part! The engine defines this function, but the CLIENT (Sandbox)
// is what implements it to return an instance of its own application.
Brynhild::Application* Brynhild::CreateApplication() 
{
  return new Sandbox();
}