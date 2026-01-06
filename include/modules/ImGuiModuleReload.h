#pragma once
#include <imgui.h>

typedef void (*PluginHello)();
typedef int (*PluginAdd)(int, int);

struct ImGuiModuleAPI {
  PluginHello hello;
  PluginAdd add;
};

typedef ImGuiModuleAPI *(*CreatePluginAPI)();
