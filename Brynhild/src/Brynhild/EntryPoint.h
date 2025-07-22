#pragma once

#ifdef BRYN_PLATFORM_WINDOWS

extern Brynhild::Application* Brynhild::CreateApplication();

int main(int* argc, char** argv) {
  Brynhild::Log::Init();
  BRYN_CLIENT_ERROR("open");
  BRYN_CORE_INFO("doors of chroma");

  
  auto app = Brynhild::CreateApplication();
  app->Run();
  delete app;
}

#endif // BRYN_PLATFORM_WINDOWS