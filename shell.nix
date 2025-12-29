{
  pkgs ? import <nixpkgs> { },
}:

pkgs.clangStdenv.mkDerivation rec {
  pname = "clang-dev-shell";
  version = "1.0";

  buildInputs = with pkgs; [
    cmake
    ninja
    bear
    pkg-config
    xorg.libX11
    xorg.libXrandr
    xorg.libXinerama
    xorg.libXcursor
    xorg.libXi
    mesa
    libGL
    libGLU
  ];

  shellHook = ''
    echo "🛠 Clang development shell"
    echo "🧪 C compiler: $(which clang)"
    echo "🧪 C++ compiler: $(which clang++)"
    echo "🔧 cmake version: $(cmake --version | head -n1)"
    echo "🚀 ninja version: $(ninja --version)"
    echo ""
  '';
}
