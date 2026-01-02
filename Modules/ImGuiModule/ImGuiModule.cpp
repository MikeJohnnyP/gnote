#include "ex_pch.h"
#include "modules/ImGuiModuleReload.h"

bool show_demo_window = true;
bool show_another_window = false;

void init() {}
void hello() {};

int add(int a, int b) { return a * b; }

extern "C" GNOTE_EXMODULE ImGuiModuleAPI *createPluginAPI() {
  static ImGuiModuleAPI api = {hello, add};
  return &api;
}

extern "C" GNOTE_EXMODULE void destroy() {
  std::cout << "Destroying ImGuiModuleAPI kkk" << std::endl;
}
