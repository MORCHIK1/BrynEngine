#pragma once

#include "Brynhild/Event/Event.h"
#include "Brynhild/Core.h"

namespace Brynhild {
  class BRYN_API Layer
  {
  public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {};
    virtual void OnDetach() {};
    virtual void OnUpdate() {};
    virtual void OnEvent(Event& event) {};
    virtual void OnImGuiDraw() {};

    inline const std::string GetName() const { return m_Name; }
  protected:
    std::string m_Name;
  };
}


