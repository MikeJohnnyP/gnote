# AGENTS.md

This file provides guidance for AI coding agents working in the Gnote game engine repository.

## Build Commands
```bash
cmake -S . -B build && cmake --build build          # Build all
cmake --build build --target <target>               # Single target (Engine, Sandbox, ImGuiModule)
rm -rf build && cmake -S . -B build && cmake --build build  # Clean build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build  # Release
./build/bin/Sandbox   # Run (Unix) | .\build\bin\Sandbox.exe (Windows)
```

## Test Commands
```bash
ctest --test-dir build                    # Run all tests
ctest --test-dir build -R <testname>      # Run single test by name pattern
ctest --test-dir build --output-on-failure  # Show output on failure
```

## Linting
```bash
clang-format -i <file>                    # Format (uses .clang-format)
clang-format --dry-run --Werror <file>    # Check without modifying
# Compilation database: build/compile_commands.json
```

## Code Style Guidelines

### Language Standards and Compilation
- **C++ Standard**: C++23 (CMAKE_CXX_STANDARD 23)
- **Extensions**: Disabled (CMAKE_CXX_EXTENSIONS OFF)
- **Compiler**: MSVC on Windows, GCC/Clang on Unix
- **Hot Reload**: Enabled for MSVC Debug builds

### Formatting (.clang-format configuration)
- **Base style**: Microsoft
- **Indentation**: 4 spaces (no tabs)
- **Column limit**: 120 characters
- **Brace style**: Allman (braces on new line)
- **Short functions**: None allowed on single line
- **Include sorting**: Disabled (preserve manual ordering)

### Naming Conventions
| Element              | Convention       | Example                          |
|---------------------|------------------|----------------------------------|
| Classes/Structs     | PascalCase       | `class Window`, `struct WindowSpec` |
| Public methods      | PascalCase       | `Init()`, `BeginScene()`         |
| Public members      | PascalCase       | `Title`, `Vsync`                 |
| Private members     | m_ prefix        | `m_window`, `m_isWindowClose`    |
| Static members      | s_ prefix        | `s_instance`, `sCoreLogger`      |
| Constants/Enums     | PascalCase       | `DrawType::Buffer`               |
| Namespaces          | PascalCase       | `Gnote`                          |
| Files               | PascalCase       | `Window.h`, `Renderer.cpp`       |
| Free functions      | camelCase        | `createWindow()`, `createSpec()` |

### Headers and Includes
- Use `#pragma once` for header guards
- Include order: project headers, third-party, standard library
- Use `pch.h` precompiled header for common includes

### Namespace and API
- All engine code lives in the `Gnote` namespace
- Decorate public APIs with `GNOTE_API` macro
- Close namespace with comment: `} // namespace Gnote`

### Smart Pointers (defined in pch.h)
```cpp
template <typename T> using Ref = std::shared_ptr<T>;
template <typename T> using Scope = std::unique_ptr<T>;
```

### Error Handling and Logging
```cpp
// Assertions (active when GNOTE_ENABLE_ASSERTS defined)
GNOTE_ASSERT(condition, "Message");       // Client-side
GNOTE_CORE_ASSERT(condition, "Message");  // Engine-side

// Logging (Debug builds only). Levels: TRACE, DEBUG, INFO, WARN, ERROR, CRITICAL
CORE_LOG_INFO("Engine: {}", value);   // Engine logging
LOG_INFO("Client: {}", value);        // Client logging
```

### Common Macros
```cpp
GNOTE_EVENT_BIND(Application::OnEvent)   // Event binding
DYNAMIC_CAST(value, Type)                // std::dynamic_pointer_cast wrapper
EVENT_CLASS(EventTypeName)               // Event class boilerplate
```

## Project Structure
```
Engine/Core/           # Core systems (Event, Layer, Logger, Renderer)
Engine/Core/Platform/  # Platform-specific (OpenGL, Windows)
Modules/               # Loadable plugins (ImGuiModule)
Sandbox/               # Example application with Assets/
Vendors/               # Dependencies: glfw, glad, glm, imgui, stb_image
```

## Build System Notes
- Binaries: `build/bin/`, Plugins: `build/bin/plugins/`
- Assets copied to `build/bin/Assets/`
- Each subproject has its own CMakeLists.txt

## Creating New Components

### New Application
```cpp
#include "Gnote.h"

class MyApp : public Gnote::Application
{
public:
    bool ClientInit() override { return true; }
    bool ClientShutdown() override { return true; }
};

Gnote::Application* Gnote::createApplication() { return new MyApp(); }
Gnote::WindowSpec Gnote::createSpec() { /* configure window */ }
```

### New Layer
```cpp
class MyLayer : public Gnote::Layer
{
public:
    MyLayer() : Layer("MyLayer") {}
    void OnAttach() override {}
    void OnDettach() override {}
    void OnUpdate(Gnote::TimeSteps ts) override {}
    void OnEvent(Gnote::Event& event) override {}
};
```

## Agent Guidelines

### Before Making Changes
- Format code with `clang-format -i <file>` before committing
- Build both Debug and Release to verify compilation
- Follow existing patterns in similar files

### Key Patterns to Follow
- Use virtual destructors for base classes: `virtual ~ClassName() = default;`
- Use explicit for single-argument constructors
- Prefer `Ref<T>` and `Scope<T>` over raw pointers for ownership
- Keep platform-specific code in `Platform/` subdirectories
- Use factory functions for cross-platform object creation

### What to Avoid
- Raw `new`/`delete` for owned resources (use smart pointers)
- Mixing tabs and spaces (use 4 spaces only)
- Single-line function bodies
- Modifying vendor code directly
