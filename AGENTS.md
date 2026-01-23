# AGENTS.md

This document provides comprehensive guidance for agentic coding agents working within the Gnote game engine repository, including style, policies, and project structure. Adhering to these guidelines will ensure minimal friction, best maintainability, and consistent code quality throughout the codebase.

---

## Build, Test, and Lint Commands

### Build
```bash
cmake -S . -B build && cmake --build build              # Build all targets
cmake --build build --target <target>                   # Build single target (e.g. Engine, Sandbox, ImGuiModule)
rm -rf build && cmake -S . -B build && cmake --build build  # Clean build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build  # Release build
./build/bin/Sandbox          # Run on Unix
.\build\bin\Sandbox.exe      # Run on Windows
```

### Test
```bash
ctest --test-dir build                         # Run all tests
ctest --test-dir build -R <testname>           # Run a specific test (name pattern)
ctest --test-dir build --output-on-failure     # Show test output on failure
```

### Lint/Format
```bash
clang-format -i <file>                  # Reformat code (Microsoft style)
clang-format --dry-run --Werror <file>  # Lint: report formatting errors
# Compilation database: build/compile_commands.json
```

## Code Style Guidelines

### Language
- **Standard:** C++23 (`CMAKE_CXX_STANDARD 23`)
- **Extensions:** Disabled (`CMAKE_CXX_EXTENSIONS OFF`)
- **Compiler:** MSVC on Windows; GCC or Clang on Unix
- **Hot Reload:** Enabled in MSVC Debug builds (see root `CMakeLists.txt`)

### .clang-format Excerpt
```
BasedOnStyle: Microsoft
IndentWidth: 4
TabWidth: 4
UseTab: Never
ColumnLimit: 120
AllowShortFunctionsOnASingleLine: None
SortIncludes: false
IncludeBlocks: Preserve
BreakBeforeBraces: Allman
```

### Formatting and Imports
- **Indentation:** 4 spaces (no tabs), enforced via clang-format and (vendor) .editorconfig
- **Brace Style:** Allman (open braces on their own line)
- **Max Line Length:** 120 characters
- **Short Functions:** Not allowed on a single line
- **Imports:**
  - No automatic sorting (preserve manual order for predictability and extensibility)
  - Include order: project headers, third-party headers, standard library
  - Use `#pragma once` in all headers
  - Use precompiled header `pch.h` for all commonly used includes

### Naming Conventions
| Element           | Convention      | Example                          |
|-------------------|----------------|----------------------------------|
| Classes/Structs   | PascalCase     | class Window, struct WindowSpec  |
| Public Methods    | PascalCase     | Init(), BeginScene()             |
| Public Members    | PascalCase     | Title, Vsync                     |
| Private Members   | m_ prefix      | m_window, m_isWindowClose         |
| Static Members    | s_ prefix      | s_instance, sCoreLogger           |
| Constants/Enums   | PascalCase     | DrawType::Buffer                 |
| Namespaces        | PascalCase     | Gnote                            |
| Files             | PascalCase     | Window.h, Renderer.cpp           |
| Free functions    | camelCase      | createWindow(), createSpec()     |

### Types and Smart Pointers
- Use `Ref<T>` (`std::shared_ptr<T>`) and `Scope<T>` (`std::unique_ptr<T>`) over raw pointers for ownership
- Place all engine and module code within the `Gnote` namespace. Use `GNOTE_API` for public APIs.
- Use virtual destructors in base classes (`virtual ~ClassName() = default;`)
- Use `explicit` for constructors that take one argument

### Error Handling and Logging
- **Assertions:** Use `GNOTE_ASSERT` (client) and `GNOTE_CORE_ASSERT` (engine); active when `GNOTE_ENABLE_ASSERTS` is defined
- **Exceptions:** Do not throw exceptions except for truly exceptional circumstances (avoid where practical; prefer assertion)
- **Logging:** Use logger macros only in Debug builds:
  - Engine: `CORE_LOG_INFO("Engine: {}", value);`
  - Client: `LOG_INFO("Client: {}", value);`
  - Log levels: TRACE, DEBUG, INFO, WARN, ERROR, CRITICAL
  - Use the most granular log level that is appropriate for the message
- **Macros:**
  - `GNOTE_EVENT_BIND`, `DYNAMIC_CAST`, and `EVENT_CLASS` are used for event system and type safety

### Includes, API Exposure, and Project Structure
- Header guards: always `#pragma once`
- Use pch.h for all stable and frequently used includes
- Project structure:
```
Engine/Core/           # Core: Event, Layer, Logger, Renderer
Engine/Core/Platform/  # Platform-specific (e.g., OpenGL, Windows)
Modules/               # Loadable plugins (e.g. ImGuiModule)
Sandbox/               # Example app & assets
Vendors/               # Third-party dependencies (glfw, glad, glm, imgui, stb_image)
```
- Each subproject has its own CMakeLists.txt
- Binaries to `build/bin/`; plugins to `build/bin/plugins/`; assets copied to `build/bin/Assets/`

### When Adding New Code:
- **Applications**:
```cpp
#include "Gnote.h"
class MyApp : public Gnote::Application {
public:
    bool ClientInit() override { return true; }
    bool ClientShutdown() override { return true; }
};
Gnote::Application* Gnote::createApplication() { return new MyApp(); }
Gnote::WindowSpec Gnote::createSpec() { /* configure */ }
```
- **Layers:**
```cpp
class MyLayer : public Gnote::Layer {
public:
    MyLayer() : Layer("MyLayer") {}
    void OnAttach() override {}
    void OnDettach() override {}
    void OnUpdate(Gnote::TimeSteps ts) override {}
    void OnEvent(Gnote::Event& event) override {}
};
```

### Agent Guidelines
- **Before PR/Committing:**
  - Always `clang-format -i <file>` before committing.
  - Build and test in both Debug and Release modes, fix all warnings/errors.
  - Follow patterns used in similar files: prefer using platform subdirectories, avoid single-line function bodies, avoid vendor modifications, avoid raw `new`/`delete`.
  - Prefer in-place, minimal-diff PRs to ease review and integration.
- **Avoid:**
  - Mixing tabs and spaces (always use 4 spaces)
  - Modifying code in Vendors/
  - Inconsistent API signatures

### Additional Notes
- **DllManager:** Use for safe DLL load/unload; see Engine/Core/DllLoader
- **Platform/ cross-target:** Always keep platform-specific code under Platform/; use factory patterns for instantiation
- **EditorConfig:** Project uses 4-space indent and trims trailing spaces in non-vendor code (see .editorconfig in vendors for exceptions)

---

_This file is intended for all agentic and automated contributors working with the Gnote engine. Please keep it up to date with evolving best practices and tools used in the project._
