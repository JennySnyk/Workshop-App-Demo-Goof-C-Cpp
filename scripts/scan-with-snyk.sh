#!/bin/bash
# Scan script for Workshop App Demo - Goof (C++ Edition)
# This script runs all Snyk scans on the vulnerable application

set -e

echo "=================================="
echo "Goof C++ - Snyk Security Scan"
echo "=================================="
echo ""

# Check if Snyk is installed
if ! command -v snyk &> /dev/null; then
    echo "❌ Snyk CLI not found!"
    echo ""
    echo "To install Snyk CLI:"
    echo "  npm install -g snyk"
    echo "  or"
    echo "  brew install snyk"
    echo ""
    echo "Then authenticate:"
    echo "  snyk auth"
    exit 1
fi

# Check if authenticated
if ! snyk auth check &> /dev/null; then
    echo "❌ Not authenticated with Snyk!"
    echo ""
    echo "Please run:"
    echo "  snyk auth"
    exit 1
fi

echo "✅ Snyk CLI found and authenticated"
echo ""

# Create results directory
mkdir -p scan-results

# 1. Snyk Code (SAST)
echo "🔍 Running Snyk Code (SAST) scan..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
snyk code test --json > scan-results/code-scan.json || true
snyk code test
echo ""

# 2. Snyk Open Source (SCA)
echo "🔍 Running Snyk Open Source (SCA) scan..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

# Scan SBOM files
if [ -f "sbom.json" ]; then
    echo "Scanning SBOM (sbom.json)..."
    snyk test --file=sbom.json --json > scan-results/sca-sbom.json || true
    snyk test --file=sbom.json || true
    echo ""
fi

# Scan Conan files
if [ -f "conanfile.txt" ]; then
    echo "Scanning conanfile.txt..."
    snyk test --file=conanfile.txt --json > scan-results/sca-conanfile-txt.json || true
    snyk test --file=conanfile.txt || true
    echo ""
fi

if [ -f "conanfile.py" ]; then
    echo "Scanning conanfile.py..."
    snyk test --file=conanfile.py --json > scan-results/sca-conanfile-py.json || true
    snyk test --file=conanfile.py || true
    echo ""
fi

if [ ! -f "conanfile.txt" ] && [ ! -f "conanfile.py" ] && [ ! -f "sbom.json" ]; then
    echo "⚠️  No dependency files found, skipping SCA scan"
fi
echo ""

# 3. Snyk Container
echo "🔍 Running Snyk Container scan..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
if command -v docker &> /dev/null; then
    echo "Building Docker image..."
    docker build -t goof-cpp:latest . -q
    snyk container test goof-cpp:latest --json > scan-results/container-scan.json || true
    snyk container test goof-cpp:latest --file=Dockerfile
else
    echo "⚠️  Docker not found, skipping container scan"
fi
echo ""

# 4. Snyk IaC
echo "🔍 Running Snyk IaC scan..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
if [ -d "terraform" ]; then
    snyk iac test terraform/ --json > scan-results/iac-scan.json || true
    snyk iac test terraform/
else
    echo "⚠️  No terraform directory found, skipping IaC scan"
fi
echo ""

echo "=================================="
echo "Scan Complete!"
echo "=================================="
echo ""
echo "Results saved to: scan-results/"
echo ""
echo "Expected findings:"
echo "  📌 SAST: Buffer overflow, format string, command injection, etc."
echo "  📌 SCA (SBOM): OpenSSL Heartbleed, zlib CVEs, libcurl CVEs, etc."
echo "  📌 SCA (Conan): Same vulnerabilities via conanfile.txt/py"
echo "  📌 Container: Vulnerable base image, running as root, etc."
echo "  📌 IaC: Public S3 buckets, open security groups, etc."
echo ""
echo "These are INTENTIONAL vulnerabilities for training purposes!"

