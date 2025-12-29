# AGENTS.md

## Build, Lint, and Test Commands
- Build all: `cmake -S . -B build && cmake --build build`
- Build single target: `cmake --build build --target <target>`
- Clean build: `rm -rf build && cmake -S . -B build`
- Run executable: `./build/<target>` (e.g., `./build/Sandbox`)
- Run single test (if tests exist): `ctest -R <testname>` from build directory
- Lint: Use `clang-tidy` or `cppcheck` manually on source files

## Code Style Guidelines
- Use C++20 standard (see CMakeLists.txt)
- Prefer modern C++ features (auto, smart pointers, range-based for)
- Place headers in `include/` or local to module
- Use PascalCase for class names, camelCase for variables/functions
- Namespace all code (avoid global namespace pollution)
- Error handling: use exceptions for recoverable errors, assert for invariants
- Format code with `clang-format` (default style)
- Group and order includes: standard, third-party, project
- Avoid `using namespace std` in headers
- Prefer explicit types over auto in public APIs
- Document public functions/classes with Doxygen comments

## Special Rules
- No Cursor or Copilot rules detected in this repository
- If adding tests, use CTest integration via CMake
- Keep CMakeLists.txt syntax valid and minimal; prefer target-based commands

---
For more details, see CMakeLists.txt in root and subdirectories.