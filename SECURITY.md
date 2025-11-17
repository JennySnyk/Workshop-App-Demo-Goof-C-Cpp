# Security Policy

## ⚠️ Important Notice

**This repository contains INTENTIONALLY VULNERABLE code for educational and demonstration purposes.**

This application is designed to showcase various security vulnerabilities and **MUST NOT** be used in production environments.

## Purpose

This repository is designed to:

1. Demonstrate common C/C++ security vulnerabilities
2. Train developers on secure coding practices
3. Showcase security scanning tools like Snyk
4. Provide hands-on learning for security workshops

## Vulnerabilities

This application contains the following **INTENTIONAL** vulnerabilities:

### SAST (Static Application Security Testing)
- Buffer Overflow (CWE-120)
- Format String Vulnerability (CWE-134)
- SQL Injection (CWE-89)
- Command Injection (CWE-78)
- Path Traversal (CWE-22)
- Use After Free (CWE-416)
- Integer Overflow (CWE-190)
- Null Pointer Dereference (CWE-476)
- Memory Leak (CWE-401)
- Hardcoded Credentials (CWE-798)
- Insecure Randomness (CWE-330)
- Race Condition (CWE-362)

### SCA (Software Composition Analysis)
- Dependencies with known CVEs
- Outdated libraries with security issues

### Container Security
- Vulnerable base images
- Running as root user
- Exposed unnecessary ports
- Hardcoded secrets in environment variables

### Infrastructure as Code
- Public S3 buckets
- Overly permissive security groups
- Unencrypted storage
- Publicly accessible databases
- Missing monitoring and logging

## Usage Guidelines

### ✅ DO:
- Use in isolated, controlled environments only
- Use for security training and education
- Use for demonstrating security scanning tools
- Learn from the vulnerabilities and how to fix them

### ❌ DON'T:
- Deploy to production environments
- Expose to public networks
- Use on systems with sensitive data
- Use as a template for real applications
- Remove security warnings from the code

## Reporting Issues

If you find an **UNINTENDED** security issue (i.e., a vulnerability we didn't mean to include), please:

1. Open an issue in this repository
2. Describe the unintended vulnerability
3. If appropriate, suggest a fix that maintains educational value

## Learning Resources

To learn how to write secure C/C++ code:

- [SEI CERT C++ Coding Standard](https://wiki.sei.cmu.edu/confluence/display/cplusplus)
- [CWE/SANS Top 25 Most Dangerous Software Errors](https://cwe.mitre.org/top25/)
- [OWASP Top 10](https://owasp.org/www-project-top-ten/)
- [Snyk Learn](https://learn.snyk.io/)

## Disclaimer

The authors and contributors of this repository are not responsible for any misuse of this application or any damages that may result from its use. This code is provided "AS IS" for educational purposes only.

