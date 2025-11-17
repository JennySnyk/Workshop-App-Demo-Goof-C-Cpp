# Vulnerable Dependencies Source Code

This directory contains **source code snippets** from intentionally vulnerable versions of popular C/C++ libraries for Snyk Open Source scanning demonstration.

## Purpose

Snyk's C/C++ open source scanning works by analyzing the actual source code files of dependencies (not package manager files). The `snyk test --unmanaged` command scans these source files, converts them to hashes, and matches them against Snyk's vulnerability database.

## Included Vulnerable Libraries

### OpenSSL 1.0.1t
**Location**: `openssl-1.0.1t/`
**Critical CVEs**:
- CVE-2014-0160 (Heartbleed) - Memory disclosure vulnerability
- CVE-2016-2105, CVE-2016-2106, CVE-2016-2107, CVE-2016-2108

**Files**:
- `ssl.h` - SSL/TLS header with Heartbleed vulnerability definitions
- `ssl_lib.c` - Vulnerable heartbeat implementation (Heartbleed bug)

###zlib 1.2.8
**Location**: `zlib-1.2.8/`
**Critical CVEs**:
- CVE-2016-9840 - Out-of-bounds pointer arithmetic in inftrees.c
- CVE-2016-9841 - Out-of-bounds pointer arithmetic in inffast.c
- CVE-2016-9842 - Undefined left shift of negative number
- CVE-2016-9843 - Big shift exponents

**Files**:
- `zlib.h` - zlib compression library header
- `inflate.c` - Vulnerable decompression implementation

### libcurl 7.58.0
**Location**: `libcurl-7.58.0/`
**Critical CVEs**:
- CVE-2018-1000120 - FTP path trickery leads to NIL byte out of bounds write
- CVE-2018-1000121 - LDAP NULL pointer dereference
- CVE-2018-1000122 - RTSP RTP buffer over-read

**Files**:
- `curl.h` - libcurl header with API definitions
- `url.c` - Vulnerable URL parsing implementation

## How to Scan

From the repository root, run:

```bash
# Scan all dependencies in the deps/ directory
snyk test --unmanaged

# Scan with detailed output
snyk test --unmanaged --json

# Scan with severity threshold
snyk test --unmanaged --severity-threshold=high
```

## What Snyk Does

According to the [Snyk C/C++ troubleshooting documentation](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++/troubleshooting-c-c++-for-open-source):

1. **Scans source code files** - Collects C/C++ source files from the scanned directory
2. **Creates file hashes** - Converts files to hashes (your code is NOT sent to Snyk servers)
3. **Matches against database** - Compares hashes to known vulnerable library versions
4. **Reports vulnerabilities** - Shows CVEs found in the matched libraries

## Important Notes

⚠️ **These are simplified/representative source files** for demonstration purposes. They contain:
- Version identifiers that match vulnerable releases
- Actual vulnerable code patterns with comments explaining the vulnerabilities
- Sufficient file content for Snyk to match against its database

🔒 **Privacy**: Only file hashes are sent to Snyk servers, not the actual source code.

## Troubleshooting

### "Why did Snyk not find any dependencies?"

If Snyk doesn't detect these libraries, check:

1. **Source code present**: Make sure the `.h` and `.c` files are unpacked in this directory
2. **Official release match**: Files should match official release patterns
3. **Sufficient files**: Need enough files for Snyk to recognize the library
4. **Recent Snyk database**: The Snyk database updates twice monthly

For more details, see [Snyk C/C++ Troubleshooting](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++/troubleshooting-c-c++-for-open-source).

## Why Not Use Package Managers?

Snyk C/C++ scanning is different from other languages:
- ❌ Does NOT scan `conanfile.txt`, `CMakeLists.txt`, or `package.json`
- ❌ Does NOT work with SBOM files directly for C/C++
- ✅ DOES scan actual `.c`, `.cpp`, `.h`, `.hpp` source files
- ✅ DOES work with the `--unmanaged` flag

This approach works because C/C++ dependencies are often included as source code in projects, unlike other languages that use centralized package repositories.

