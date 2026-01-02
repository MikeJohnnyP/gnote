#include "ex_pch.h"
#include "modules/ImGuiModuleReload.h"

void hello() { std::cout << "Hello from ImGuiModule here" << std::endl; };

int add(int a, int b) { return a * b; }

extern "C" GNOTE_EXMODULE ImGuiModuleAPI *createPluginAPI() {
  static ImGuiModuleAPI api = {hello, add};
  return &api;
}

extern "C" GNOTE_EXMODULE void destroy() {
  std::cout << "Destroying ImGuiModuleAPI kkk" << std::endl;
}
