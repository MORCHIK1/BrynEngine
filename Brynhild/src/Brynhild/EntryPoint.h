#pragma once

#ifdef BRYN_PLATFORM_WINDOWS

extern Brynhild::Application* Brynhild::CreateApplication();

int main(int* argc, char** argv) {
  auto app = Brynhild::CreateApplication();
  app->Run();
  delete app;
}

#endif // BRYN_PLATFORM_WINDOWS