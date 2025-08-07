#pragma once

#include "Brynhild/Layer.h"

#include "Brynhild/Event/ApplicationEvent.h"
#include "Brynhild/Event/KeyEvent.h"
#include "Brynhild/Event/MouseEvent.h"


namespace Brynhild {
  class BRYN_API ImGuiLayer : public Layer{
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach() override;
    void OnDetach() override;

    void OnImGuiDraw() override;

    void Begin();
    void End();
  };
}
