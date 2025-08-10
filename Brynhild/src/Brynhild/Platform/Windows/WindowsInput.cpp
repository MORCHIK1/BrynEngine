#include "PreCompiledHeader.h"
#include "WindowsInput.h"
#include <GLFW/glfw3.h>

#include "Brynhild/Application.h"

namespace Brynhild {
  Input* Input::s_InputInstance = new WindowsInput();

  bool WindowsInput::IsKeyPressedImpl(int keycode)
  {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);

    return state == GLFW_PRESS || state == GLFW_RELEASE;
  }
  bool WindowsInput::IsMouseButtonPressedImpl(int keycode)
  {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, keycode);

    return state == GLFW_PRESS || state == GLFW_RELEASE;
  }
  float WindowsInput::GetMouseXImpl()
  {
    auto [x, y] = GetMousePosImpl();
    return x;
  }
  float WindowsInput::GetMouseYImpl()
  {
    auto [x, y] = GetMousePosImpl();
    return y;
  }
  std::pair<float, float> WindowsInput::GetMousePosImpl()
  {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return { static_cast<float>(xpos), static_cast<float>(ypos) };
  }
}
