#pragma once

#include "PreCompiledHeader.h"
#include "Brynhild/Core.h"
#include "Brynhild/Event/Event.h"

namespace Brynhild {
	struct WindowProps
	{
		std::string Title;
		unsigned int Height;
		unsigned int Width;

		WindowProps(const std::string& title = "Brynhild Engine", 
			unsigned int height = 720, 
			unsigned int width = 1280) 
			: Title(title), Height(height), Width(width) {}
	};

	class BRYN_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual unsigned int GetHeight() const = 0;
		virtual unsigned int GetWidth() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}