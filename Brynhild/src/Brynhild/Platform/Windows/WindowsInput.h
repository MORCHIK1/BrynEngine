#pragma once
#include "Brynhild/Input.h"

namespace Brynhild {
  class WindowsInput : public Input
  {
  protected:
    bool IsKeyPressedImpl(int keycode) override;

    bool IsMouseButtonPressedImpl(int button) override;

    float GetMouseXImpl() override;
    float GetMouseYImpl() override;
    std::pair<float, float> GetMousePosImpl() override;
  };
}


