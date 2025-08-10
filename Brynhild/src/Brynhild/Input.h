#pragma once

#include "Brynhild/Core.h"

namespace Brynhild {
  class BRYN_API Input {
  public:
    inline static bool IsKeyPressed(int keycode) { return s_InputInstance->IsKeyPressedImpl(keycode); }
    inline static bool IsMouseButtonPressed(int button) { return s_InputInstance->IsMouseButtonPressedImpl(button); }

    inline static float GetMouseX() { return s_InputInstance->GetMouseXImpl(); }
    inline static float GetMouseY() { return s_InputInstance->GetMouseYImpl(); }

    inline static std::pair<float, float> GetMousePos() { return s_InputInstance->GetMousePosImpl(); }
  protected:
    virtual bool IsKeyPressedImpl(int keycode) = 0;
    virtual bool IsMouseButtonPressedImpl(int button) = 0;
    virtual float GetMouseXImpl() = 0;
    virtual float GetMouseYImpl() = 0;
    virtual std::pair<float, float> GetMousePosImpl() = 0;
  private:
    static Input* s_InputInstance;
  };
}