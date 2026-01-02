#!/bin/bash
TARGET="Sandbox"
case "$1" in
    "build")
        cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DGLFW_BUILD_WAYLAND=OFF -DGLFW_BUILD_X11=ON
        cmake --build build
        ;;
    "run")
        if [ -f ./build/$TARGET/$TARGET ]; then
            ./build/$TARGET/$TARGET
        else
            echo "Executable $TARGET not found! Please build first."
            exit 1
        fi
        ;;
    "clean build")
        rm -rf build
        cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DGLFW_BUILD_WAYLAND=OFF -DGLFW_BUILD_X11=ON
        cmake --build build
        ;;
    *)
        echo "Usage: $0 {build|run|clean build}"
        exit 1
        ;;
esac
