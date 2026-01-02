#include "Engine.h"
#include <imgui.h>
#include <iostream>

#include <raylib.h>
#include <raymath.h>
#include <rlImGui.h>
#include <rlImGuiColors.h>

#include "Core/DllLoader/DllManager.h"
#include "Core/DllLoader/LoadLibrary.h"
#include "Core/Logger/Logger.h"
#include "modules/ImGuiModuleReload.h"

time_t getFileModTime(const char *path) {
  struct stat result;
  if (stat(path, &result) == 0) {
    return result.st_mtime;
  }
  return 0;
}

void initializeEngine() {
  Gnote::Logger::Init();
  const char *exampleModule = "./build/bin/plugins/libImGuiModule.so";
  time_t lastModTime = getFileModTime(exampleModule);
  void *handle = nullptr;
  ImGuiModuleAPI *api = nullptr;

  Gnote::DllManager::Init();
  Gnote::DllManager::LoadDll("ImGuiModule", exampleModule);

  while (true) {
    Gnote::DllManager::UpdateDlls();
    api = Gnote::DllManager::GetStructModuleAPI<ImGuiModuleAPI *>(
        "ImGuiModule", "createPluginAPI");
    if (api) {
      api->hello();
      int result = api->add(5, 3);
      std::cout << "Result of add(5, 3): " << result << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1)); // kiểm tra mỗi giây
  }
  // // Khi thoát, nhớ unload
  // if (api) {
  //   api = nullptr;
  // }
  // if (handle) {
  //   Gnote::unloadLibrary(handle);
  // }

  Gnote::DllManager::Shutdown();
}
