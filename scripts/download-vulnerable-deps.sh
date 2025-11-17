#!/bin/bash
# Script to download actual vulnerable library source code for Snyk scanning
# These are REAL vulnerable versions - DO NOT use in production!

set -e

echo "=================================="
echo "Downloading Vulnerable Dependencies"
echo "=================================="
echo ""
echo "⚠️  WARNING: These are intentionally vulnerable versions!"
echo "   Only for security training and demonstration."
echo ""

# Create deps directory
mkdir -p deps
cd deps

# Clean up any existing files
echo "🧹 Cleaning up old files..."
rm -rf openssl-* zlib-* curl-* *.tar.gz
echo ""

# Download OpenSSL 1.0.1t (contains Heartbleed - CVE-2014-0160)
echo "📥 Downloading OpenSSL 1.0.1t (Heartbleed vulnerability)..."
curl -k -L -o openssl-1.0.1t.tar.gz https://www.openssl.org/source/old/1.0.1/openssl-1.0.1t.tar.gz
echo "📦 Extracting OpenSSL 1.0.1t..."
tar -xzf openssl-1.0.1t.tar.gz
rm openssl-1.0.1t.tar.gz
echo "✅ OpenSSL 1.0.1t ready"
echo ""

# Download zlib 1.2.8 (CVE-2016-9840, CVE-2016-9841, CVE-2016-9842, CVE-2016-9843)
echo "📥 Downloading zlib 1.2.8 (multiple CVEs)..."
curl -k -L -o zlib-1.2.8.tar.gz https://www.zlib.net/fossils/zlib-1.2.8.tar.gz
echo "📦 Extracting zlib 1.2.8..."
tar -xzf zlib-1.2.8.tar.gz
rm zlib-1.2.8.tar.gz
echo "✅ zlib 1.2.8 ready"
echo ""

# Download libcurl 7.58.0 (CVE-2018-1000120, CVE-2018-1000121, CVE-2018-1000122)
echo "📥 Downloading libcurl 7.58.0 (FTP and LDAP vulnerabilities)..."
curl -k -L -o curl-7.58.0.tar.gz https://github.com/curl/curl/releases/download/curl-7_58_0/curl-7.58.0.tar.gz
echo "📦 Extracting libcurl 7.58.0..."
tar -xzf curl-7.58.0.tar.gz
rm curl-7.58.0.tar.gz
echo "✅ libcurl 7.58.0 ready"
echo ""

cd ..

echo "=================================="
echo "✅ Download Complete!"
echo "=================================="
echo ""
echo "Downloaded vulnerable libraries:"
echo "  📁 deps/openssl-1.0.1t/ - OpenSSL with Heartbleed"
echo "  📁 deps/zlib-1.2.8/ - zlib with buffer overflow CVEs"
echo "  📁 deps/curl-7.58.0/ - libcurl with injection vulnerabilities"
echo ""
echo "Now run: snyk test --unmanaged"
echo ""
echo "⚠️  These are REAL vulnerable source files - never use in production!"

