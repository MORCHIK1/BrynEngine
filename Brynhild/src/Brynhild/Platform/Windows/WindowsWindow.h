#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Brynhild/Event/EventLog.h"
#include "Brynhild/Event/ApplicationEvent.h"
#include "Brynhild/Event/MouseEvent.h"
#include "Brynhild/Event/KeyEvent.h"
#include "Brynhild/Window.h"

namespace Brynhild {
  class WindowsWindow : public Window{
  public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();

    void OnUpdate() override;

    inline unsigned int GetHeight() const override { return m_Data.Height; }
    inline unsigned int GetWidth() const override { return m_Data.Width; }

    inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
    void SetVSync(bool enabled) override;
    bool IsVSync() const override { return m_Data.VSync; }

    inline virtual void* GetNativeWindow() const { return m_Window; }
  private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();

    GLFWwindow* m_Window;

    struct WindowData {
      std::string Title;
      unsigned int Height;
      unsigned int Width;

      bool VSync;

      EventCallbackFn EventCallback;
    };

    WindowData m_Data;
  };
}