# AGENTS.md

## Build, Lint, and Test Commands
- Build all targets: `cmake -S . -B build && cmake --build build`
- Build a single target: `cmake --build build --target <target>`
- Clean build: `rm -rf build && cmake -S . -B build`
- Run executable: `./build/<target>` (e.g., `./build/Sandbox`)
- Run a single test: `ctest -R <testname>` (from build directory)
- Lint: Run `clang-tidy` or `cppcheck` manually on source files

## Code Style Guidelines
- Use C++20 (see CMakeLists.txt)
- Prefer modern C++: smart pointers, range-based for, `auto` (avoid in public APIs)
- Place headers in `include/` or module-local directories
- Naming: PascalCase for classes, camelCase for variables/functions
- Namespace all code (avoid global namespace pollution)
- Error handling: use exceptions for recoverable errors, `assert` for invariants
- Format code with `clang-format` (default style)
- Include order: standard, third-party, then project headers
- Avoid `using namespace std` in headers
- Document public APIs with Doxygen comments

## Agent Guidance
- Strictly follow these conventions and commands
- Prefer explicit, readable code and minimal dependencies
- Add tests using CTest integration via CMake
- Keep CMakeLists.txt minimal and target-based
- See CMakeLists.txt in root and subdirectories for details
- No Cursor or Copilot rules present as of Jan 2026
