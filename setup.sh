#!/bin/bash
set -e

MLX_TAR="mlx.tar.gz"
MLX_DIR="MLX42"


extract_mlx() {
    echo "📦 Checking MLX folder..."
    if [ ! -d "$MLX_DIR" ]; then
        if [ -f "$MLX_TAR" ]; then
            echo "📦 Extracting MLX..."
            tar -xzf "$MLX_TAR"
        else
            echo "⚠️  Error: $MLX_TAR not found. Please put the tar.gz in the project folder."
            exit 1
        fi
    else
        echo "✅ MLX folder already exists"
    fi
}


check_linux_libs() {
    echo "🔍 Checking required packages for MLX on Linux..."
    REQUIRED_PACKAGES=(
        libglfw3-dev
        libx11-dev
        libxcursor-dev
        libxrandr-dev
        libxinerama-dev
        libxi-dev
        libglew-dev
    )

    for pkg in "${REQUIRED_PACKAGES[@]}"; do
        if dpkg -s "$pkg" >/dev/null 2>&1; then
            echo "✅ $pkg is already installed"
        else
            echo "⚠️  $pkg is not installed, installing..."
            sudo apt update
            sudo apt install -y "$pkg"
        fi
    done
}


OS_NAME=$(uname -s)
echo "💻 Detected OS: $OS_NAME"

if [ "$OS_NAME" = "Linux" ]; then
    extract_mlx
    check_linux_libs
elif [ "$OS_NAME" = "Darwin" ]; then
    extract_mlx
    echo "✅ macOS detected, no additional libraries required"
else
    echo "⚠️  Unsupported OS: $OS_NAME"
    exit 1
fi


echo "🔧 Running make..."
make
echo "🏁 Build complete! You can now run ./cub3D"
