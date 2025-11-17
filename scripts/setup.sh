#!/bin/bash
# Setup script for Workshop App Demo - Goof (C++ Edition)

set -e

echo "=================================="
echo "Goof C++ - Setup Script"
echo "=================================="
echo ""

# Detect OS
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macos"
else
    echo "❌ Unsupported OS: $OSTYPE"
    exit 1
fi

echo "Detected OS: $OS"
echo ""

# Install dependencies
echo "📦 Installing dependencies..."
if [ "$OS" == "linux" ]; then
    sudo apt-get update
    sudo apt-get install -y g++ cmake make libssl-dev libcurl4-openssl-dev
elif [ "$OS" == "macos" ]; then
    if ! command -v brew &> /dev/null; then
        echo "❌ Homebrew not found. Please install it first: https://brew.sh"
        exit 1
    fi
    brew install cmake openssl curl
fi

echo "✅ Dependencies installed"
echo ""

# Create build directory
echo "🔨 Creating build directory..."
mkdir -p build
cd build

# Configure with CMake
echo "⚙️  Configuring with CMake..."
cmake ..

# Build
echo "🔨 Building application..."
make

echo ""
echo "✅ Build complete!"
echo ""
echo "To run the application:"
echo "  cd build"
echo "  ./goof-server"
echo ""
echo "⚠️  Remember: This application is intentionally vulnerable!"
echo "   Use only in isolated, controlled environments."

