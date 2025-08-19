#pragma once


namespace Brynhild {

  class GraphicsContext {
public:
  virtual void Init() const = 0;
  virtual void SwapBuffers() const = 0;
  };

}
