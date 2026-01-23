# Gnote 📝

> A blazing-fast note-taking app that you probably don’t need — but I built it anyway.

Gnote is a **lightweight note-taking application** built with **C++**, **Dear ImGui**, and **OpenGL**.  
It started as a personal playground to learn **C++**, **graphics**, and **system programming**, and slowly turned into something usable (at least for me).

This project is **not trying to compete** with existing note apps.  
It exists because I wanted to understand how things work under the hood.

## ✨ What is this project?
- CMake & cross-platform build
- Dear ImGui internals
- OpenGL rendering pipeline
- Platform-specific code (Win32 vs Linux)

## Motivation
I wanted to:
- Learn modern **C++ (C++20 / C++23)**
- Understand **ImGui**, **OpenGL**, and rendering pipelines
- Work with **CMake**, cross-platform builds, and CI

Building yet another note-taking app just happened to be a convenient excuse.

## 🚀 Features (current & planned)

### ✅ Current
- Lightweight ImGui-based UI
- OpenGL renderer abstraction
- Modular engine architecture
- Cross-platform build system (CMake)
- Runs on Windows, partially on Linux

### 🛠 Planned / In progress
- Better Linux support
- ... More features coming soon!

## 🖥 Platform support

| Platform | Status |
|--------|--------|
| Windows | ✅ Fully supported |
| Linux  | ⚠️ Partially supported |
| macOS  | ❌ Untested (no Mac 😭) |

- Windows is the main development platform.
- Linux builds with **clang**, but may require extra system dependencies (OpenGL, X11, etc).
- macOS support is welcome if someone wants to help 👀

## 🧱 Tech stack

- **Language**: C++ (C++20 / C++23)
- **Build system**: CMake + Presets
- **Compiler**: MSVC / clang
- **UI**: Dear ImGui
- **Rendering**: OpenGL
- **Windowing**: GLFW
- **Math**: GLM
- **CI**: GitHub Actions

## 📦 Dependencies

Vendored directly in the repo:

```cmake
add_subdirectory(Vendors/glfw)
add_subdirectory(Vendors/imgui)
add_subdirectory(Vendors/stb_image)
add_subdirectory(Vendors/glad)
add_subdirectory(Vendors/glm)
```

## 🛠 Build from source

> ⚠️ This section is still evolving.

Requirements

- CMake ≥ 3.25

- Ninja

C++ compiler:
- Windows: MSVC 19.50.35723

- Linux: clang 21.1.8

OpenGL development libraries (Linux)


```cmake
# Example (Linux, clang)
cmake --preset linux-clang-release
cmake --build --preset linux-clang-release
```

```cmake
# Example (Windows, MSVC)
cmake --preset msvc-release
cmake --build --preset msvc-release
```

## 🧪 Why another note-taking app?

Because:

- I wanted to learn C++ seriously

- I wanted to understand how desktop apps actually work

- Tutorials weren’t painful enough

- Building real software exposes real problems

This project is more about the journey than the destination.

## 🧩 Contributing

Contributions are welcome, especially if you want to help with:

- Linux / macOS support

- Build system improvements

- Code cleanup & refactors

- Documentation

Just open a PR or an issue — no strict rules here.

## 📜 License
MIT License — do whatever you want with it. See [LICENSE](LICENSE) for details.

## ❤️ Final note

If you’re learning C++, graphics programming, or CMake — feel free to dig around, break things, and ask questions.

This project exists because I was curious.


