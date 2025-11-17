# Workshop App Demo - Goof (C++ Edition)

![Security Warning](https://img.shields.io/badge/⚠️-DELIBERATELY_VULNERABLE-red?style=for-the-badge)
![Language](https://img.shields.io/badge/C++-11-blue?style=for-the-badge&logo=c%2B%2B)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

This is a **DELIBERATELY VULNERABLE** C++ application created for security demonstration and training purposes. It showcases various security vulnerabilities commonly found in C/C++ applications, making it an ideal tool for security workshops, training sessions, and demonstrating Snyk's capabilities for C++ code analysis.

## ⚠️ WARNING

**This application contains intentional security vulnerabilities and MUST NOT be deployed in production environments or on public-facing servers.**

## 🎯 Features

This repository demonstrates:

* **SAST Vulnerabilities**: 12+ examples of common C/C++ security issues based on OWASP Top 10 and CWE
* **SCA Vulnerabilities**: Dependencies with known vulnerabilities (via Conan package manager)
* **Container Vulnerabilities**: Dockerfiles using vulnerable base images and insecure configurations
* **IaC Misconfigurations**: Terraform files with common cloud security flaws

## 📸 Screenshot

```
=== Workshop App Demo - Goof (C++ Edition) ===
=== DELIBERATELY VULNERABLE - FOR TRAINING ONLY ===

Select a vulnerability to demonstrate:

1.  Buffer Overflow
2.  Format String Vulnerability
3.  SQL Injection (Simulated)
4.  Command Injection
5.  Path Traversal
6.  Use After Free
7.  Integer Overflow
8.  Null Pointer Dereference
9.  Memory Leak
10. Hardcoded Credentials
11. Insecure Randomness
12. Race Condition
0.  Exit
```

## 🚀 Getting Started

### Prerequisites

- **C++ Compiler**: GCC 7+ or Clang 6+
- **CMake**: Version 3.10 or higher
- **Conan** (optional): For dependency management
- **Docker** (optional): For containerized demos
- **Terraform** (optional): For IaC scanning demos

### Installation & Running

#### Option 1: Direct Build (Linux/macOS)

```bash
# Clone the repository
git clone <repository-url>
cd Workshop-App-Demo-Goof-CPP

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the application
make

# Run the application
./goof-server
```

#### Option 2: Using Conan for Dependency Management

```bash
# Install Conan if not already installed
pip install conan

# Install dependencies
mkdir build && cd build
conan install .. --build=missing

# Configure and build
cmake .. -DCMAKE_BUILD_TYPE=Release
make

# Run the application
./goof-server
```

**Note for Snyk Scanning**: The repository includes both `conanfile.txt` and `conanfile.py` formats. Snyk Open Source supports scanning Conan dependencies. Make sure to run `snyk test --file=conanfile.txt` or `snyk test --file=conanfile.py` from the project root directory.

#### Option 3: Using Docker

```bash
# Build the Docker image
docker build -t goof-cpp:latest .

# Run the container
docker run -it goof-cpp:latest
```

## 🐛 Vulnerability Catalog

This application includes the following intentional vulnerabilities:

### 1. Buffer Overflow (CWE-120)
**Severity**: 🔴 Critical

Unbounded string copy that can overflow the buffer.

```cpp
// Vulnerable code in server.cpp
void bufferOverflowVulnerability(const char* input) {
    char buffer[64];
    strcpy(buffer, input);  // No bounds checking!
}
```

**How to trigger**:
- Select option 1
- Enter a string longer than 64 characters
- Example: `AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA`

### 2. Format String Vulnerability (CWE-134)
**Severity**: 🔴 Critical

User input directly used in format string, allowing memory disclosure and code execution.

**How to trigger**:
- Select option 2
- Enter format specifiers: `%x %x %x %x %s`
- Can leak stack memory addresses

### 3. SQL Injection (CWE-89)
**Severity**: 🔴 Critical

Simulated SQL injection through string concatenation.

**How to trigger**:
- Select option 3
- Enter: `1 OR 1=1`
- Enter: `1; DROP TABLE users--`

### 4. Command Injection (CWE-78)
**Severity**: 🔴 Critical

Unsanitized user input passed to system() call.

**How to trigger**:
- Select option 4
- Enter: `8.8.8.8; ls -la`
- Enter: `localhost && whoami`

### 5. Path Traversal (CWE-22)
**Severity**: 🟠 High

No validation on file paths allows accessing arbitrary files.

**How to trigger**:
- Select option 5
- Enter: `../../../../etc/passwd` (Linux/macOS)
- Enter: `..\..\..\..\windows\system32\drivers\etc\hosts` (Windows)

### 6. Use After Free (CWE-416)
**Severity**: 🔴 Critical

Memory accessed after being freed, leading to crashes or exploitation.

**How to trigger**:
- Select option 6
- Demonstrates use-after-free and potential double-free

### 7. Integer Overflow (CWE-190)
**Severity**: 🟠 High

Arithmetic operations without overflow checking.

**How to trigger**:
- Select option 7
- Enter: `2147483647` (maximum int value)
- Causes overflow when adding 100

### 8. Null Pointer Dereference (CWE-476)
**Severity**: 🟠 High

Dereferencing pointers without null checks.

**How to trigger**:
- Select option 8
- Enter: `0` (don't allocate)
- Causes segmentation fault

### 9. Memory Leak (CWE-401)
**Severity**: 🟡 Medium

Allocated memory never freed, causing resource exhaustion.

**How to trigger**:
- Select option 9
- Leaks approximately 4KB of memory per call

### 10. Hardcoded Credentials (CWE-798)
**Severity**: 🔴 Critical

Credentials hardcoded directly in source code.

**How to trigger**:
- Select option 10
- Username: `admin`
- Password: `password123`

### 11. Insecure Randomness (CWE-330)
**Severity**: 🟠 High

Using `rand()` for security-sensitive operations.

**How to trigger**:
- Select option 11
- Generates predictable "random" tokens

### 12. Race Condition (CWE-362)
**Severity**: 🟡 Medium

Unsynchronized access to shared resources.

**How to trigger**:
- Select option 12
- Multiple calls show inconsistent counter values

## 🔍 Scanning with Snyk

> **📖 For detailed scanning instructions, see [SCANNING.md](SCANNING.md)**

### Prerequisites for Snyk Scanning

```bash
# Install Snyk CLI
npm install -g snyk

# Or via Homebrew
brew install snyk

# Authenticate
snyk auth
```

### Snyk Code (SAST)

Scan the source code for security vulnerabilities:

```bash
# Scan for code vulnerabilities
snyk code test

# Generate JSON report
snyk code test --json > sast-results.json
```

**Expected findings**: Buffer overflow, format string, command injection, SQL injection, use-after-free, null pointer dereference, memory leaks, hardcoded credentials, and more.

### Snyk Open Source (SCA)

Scan dependencies for known vulnerabilities:

```bash
# Option 1: Scan using Conan files
snyk test --file=conanfile.txt
# or
snyk test --file=conanfile.py

# Option 2: Scan using SBOM (Software Bill of Materials)
snyk test --sbom
# or specify the SBOM file explicitly
snyk test --file=sbom.json
snyk test --file=sbom.xml

# Option 3: Test individual packages
snyk test --package-manager=cpp --packages=pkg:conan/openssl@1.0.1t

# Monitor project for continuous monitoring
snyk monitor --file=conanfile.txt
```

**SBOM Scanning**: This project includes pre-generated SBOM files (`sbom.json` and `sbom.xml`) in CycloneDX format with `pkg:conan` identifiers. You can test the SBOM directly with `snyk test --file=sbom.json` for quick vulnerability scanning without building dependencies.

**Expected findings**: This project uses intentionally vulnerable versions with known CVEs:

- **OpenSSL 1.0.1t**: Heartbleed (CVE-2014-0160), CVE-2016-2105, CVE-2016-2106, and more
- **zlib 1.2.8**: CVE-2016-9840, CVE-2016-9841, CVE-2016-9842, CVE-2016-9843
- **libcurl 7.58.0**: Multiple security vulnerabilities including CVE-2018-1000120, CVE-2018-1000121
- **Boost 1.69.0**: Known security issues
- **SQLite 3.16.0**: Multiple CVEs
- **libxml2 2.9.4**: XXE vulnerabilities and other CVEs
- **JsonCpp 1.8.4**: Potential security issues

### Snyk Container

Scan Docker images for vulnerabilities:

```bash
# Build the image first
docker build -t goof-cpp:latest .

# Scan the container
snyk container test goof-cpp:latest

# Scan with Dockerfile analysis
snyk container test goof-cpp:latest --file=Dockerfile
```

Expected findings: Vulnerable Ubuntu base image, running as root, exposed ports, etc.

### Snyk Infrastructure as Code (IaC)

Scan Terraform files for misconfigurations:

```bash
# Scan IaC files
snyk iac test terraform/

# Detailed report
snyk iac test terraform/ --json
```

Expected findings: Publicly accessible S3 buckets, open security groups, unencrypted resources, etc.

## 📚 Educational Use Cases

This repository is perfect for:

1. **Security Training Workshops**: Demonstrate real-world vulnerabilities
2. **AppSec Tool Demos**: Show SAST/SCA/Container/IaC scanning capabilities
3. **Secure Coding Training**: Teach developers to identify and fix vulnerabilities
4. **CTF Events**: Use as vulnerable challenges
5. **CI/CD Pipeline Integration**: Test security scanning in pipelines

## 🛠️ Building for Different Platforms

### Linux

```bash
mkdir build && cd build
cmake ..
make
./goof-server
```

### macOS

```bash
# Install dependencies via Homebrew (if needed)
brew install cmake openssl curl

mkdir build && cd build
cmake ..
make
./goof-server
```

### Windows (Visual Studio)

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
.\Release\goof-server.exe
```

## 🐳 Docker Examples

### Basic Build and Run

```bash
docker build -t goof-cpp .
docker run -it goof-cpp
```

### Alpine-based Image

```bash
docker build -f Dockerfile.alpine -t goof-cpp:alpine .
docker run -it goof-cpp:alpine
```

## ☁️ Terraform Infrastructure

The `terraform/` directory contains intentionally vulnerable infrastructure as code:

```bash
cd terraform

# Initialize Terraform
terraform init

# Plan (review what would be created)
terraform plan

# NOTE: Do NOT actually apply this infrastructure!
# It contains severe security misconfigurations
# terraform apply  # DON'T RUN THIS
```

## 🧪 Running Tests

```bash
# Add tests directory (example)
mkdir tests
cd tests

# Run with Valgrind to detect memory issues
valgrind --leak-check=full ../build/goof-server
```

## 📚 Documentation

- **[SCANNING.md](SCANNING.md)** - Complete guide to scanning this repository with Snyk
- **[VULNERABILITIES.md](VULNERABILITIES.md)** - Reference of all intentional vulnerabilities
- **[SECURITY.md](SECURITY.md)** - Security policy and responsible usage

## 📖 Learning Resources

- [OWASP Top 10](https://owasp.org/www-project-top-ten/)
- [CWE Top 25](https://cwe.mitre.org/top25/)
- [Snyk Documentation](https://docs.snyk.io/)
- [Snyk C/C++ Support](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++)
- [C++ Secure Coding Guidelines](https://wiki.sei.cmu.edu/confluence/display/cplusplus)

## 🤝 Contributing

This is an educational project. If you have suggestions for additional vulnerabilities or improvements, feel free to contribute!

## ⚖️ License

This project is licensed under the MIT License - see the LICENSE file for details.

## 📧 Contact

For questions or feedback about this workshop application:
- Create an issue in this repository
- Contact your Snyk representative

## 🙏 Acknowledgments

- Inspired by the original [Goof](https://github.com/snyk/goof) vulnerable application
- Based on OWASP and CWE vulnerability classifications
- Created for Snyk security workshops and demonstrations

---

**Remember**: This application is intentionally vulnerable. Never deploy it in production or on publicly accessible servers. Use it only in controlled, isolated environments for educational purposes.

