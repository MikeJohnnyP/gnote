#include "Engine.h"
#include <imgui.h>
#include <iostream>

#include <raylib.h>
#include <raymath.h>
#include <rlImGui.h>
#include <rlImGuiColors.h>

#include "Core/Logger/Logger.h"

void initializeEngine() { // Initialization
  //--------------------------------------------------------------------------------------
  Gnote::Logger::Init();
  int screenWidth = 1280;
  int screenHeight = 720;

  // do not set the FLAG_WINDOW_HIGHDPI flag, that scales a low res framebuffer
  // up to the native resolution. use the native resolution and scale your
  // geometry.
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  InitWindow(screenWidth, screenHeight,
             "raylib-Extras [ImGui] example - Editor Example");
  SetTargetFPS(60);
  rlImGuiSetup(true);
  ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

  bool opened = true;
  bool isCheck = false;

  const char *hello[] = {"Prev", "Current", "Last"};
  int currentItem = 2;
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {

    BeginDrawing();
    ClearBackground(DARKGRAY);

    rlImGuiBegin();

    if (ImGui::Begin("My Gui App", &opened)) {
      if (ImGui::Button("Hello")) {
      }

      ImGui::Checkbox("My checkbox", &isCheck);
      ImGui::Combo("##combo1", &currentItem, hello, IM_ARRAYSIZE(hello));
      ImGui::Text("This is my text");
    }

    ImGui::End();

    rlImGuiEnd();

    EndDrawing();
    //----------------------------------------------------------------------------------
  }
  rlImGuiShutdown();

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------
}
