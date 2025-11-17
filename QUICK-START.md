# Quick Start Guide - Snyk C/C++ Scanning

## ⚠️ Important: Correct Scanning Method

C/C++ scanning in Snyk is **different** from other languages. Use the `--unmanaged` flag to scan source code files.

## ✅ Correct Commands

```bash
# Scan C/C++ dependencies
snyk test --unmanaged

# Scan with JSON output
snyk test --unmanaged --json > results.json

# Scan SAST (code vulnerabilities)
snyk code test
```

## ❌ These DON'T Work for C/C++

```bash
# ❌ WRONG - C/C++ doesn't support package manager file scanning
snyk test --file=conanfile.txt

# ❌ WRONG - SBOM files not supported for unmanaged C/C++
snyk test --file=sbom.json

# ❌ WRONG - Package manager flag doesn't work for C/C++
snyk test --package-manager=cpp
```

## 📁 What Gets Scanned?

The `--unmanaged` flag scans:
- `.c` files (C source)
- `.cpp`, `.cxx`, `.cc` files (C++ source)
- `.h` files (C headers)
- `.hpp`, `.hxx` files (C++ headers)

In this repository:
- `deps/openssl-1.0.1t/` - OpenSSL source with Heartbleed
- `deps/zlib-1.2.8/` - zlib source with CVEs
- `deps/libcurl-7.58.0/` - libcurl source with vulnerabilities

## 🔍 How It Works

According to [Snyk's C/C++ troubleshooting docs](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++/troubleshooting-c-c++-for-open-source):

1. **Collects source files** from the scanned directory
2. **Creates file hashes** (your code is NOT sent to Snyk - only hashes!)
3. **Matches hashes** against Snyk's vulnerability database
4. **Reports CVEs** found in matched library versions

## 🚀 Quick Demo (5 minutes)

```bash
# Clone the repository
git clone https://github.com/JennySnyk/Workshop-App-Demo-Goof-C-Cpp.git
cd Workshop-App-Demo-Goof-C-Cpp

# Authenticate (if not already)
snyk auth

# Scan for vulnerable C/C++ dependencies
snyk test --unmanaged

# Scan for code vulnerabilities (SAST)
snyk code test
```

## 📊 Expected Results

### Unmanaged Scan (`snyk test --unmanaged`)
- ✅ Detects **OpenSSL 1.0.1t** - Heartbleed (CVE-2014-0160)
- ✅ Detects **zlib 1.2.8** - 4 critical CVEs
- ✅ Detects **libcurl 7.58.0** - Multiple vulnerabilities

### Code Scan (`snyk code test`)
- ✅ Detects 12+ vulnerabilities in `server.cpp`:
  - Buffer Overflow
  - Format String
  - Command Injection
  - Use After Free
  - And more...

## 🆘 Troubleshooting

**Error: "Could not detect package manager for file: conanfile.txt"**

✅ **Solution**: Don't use `--file=conanfile.txt`. Use `--unmanaged` instead:
```bash
snyk test --unmanaged
```

**Error: "No dependencies found"**

Check:
1. Source files exist in `deps/` directory
2. Files are actual `.c`, `.cpp`, `.h` files
3. Run from the repository root directory

## 📚 More Information

- **[README.md](README.md)** - Full repository documentation
- **[SCANNING.md](SCANNING.md)** - Detailed scanning guide
- **[deps/README.md](deps/README.md)** - About the vulnerable dependencies
- **[Snyk C/C++ Docs](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++)**
- **[Troubleshooting Guide](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++/troubleshooting-c-c++-for-open-source)**

## 💡 Key Takeaways

1. ✅ Use `snyk test --unmanaged` for C/C++ dependencies
2. ✅ Use `snyk code test` for C/C++ SAST
3. ❌ Don't use `--file=conanfile.txt` or `--file=sbom.json`
4. 🔒 Only file hashes are sent to Snyk (not source code)
5. 📁 Place vulnerable library source in `deps/` directory

---

**⚠️ REMINDER**: This is a deliberately vulnerable application for training purposes only!

