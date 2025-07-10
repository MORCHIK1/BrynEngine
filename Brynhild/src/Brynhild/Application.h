#pragma once

#include "Core.h"

namespace Brynhild 
{
  class BRYN_API Application
  {
  public:
    Application();
    virtual ~Application();

    void Run();
  };

  //Will be defined in client(sandbox)
  Application* CreateApplication();
}