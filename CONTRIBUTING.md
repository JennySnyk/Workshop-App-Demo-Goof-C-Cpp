# Contributing to Workshop App Demo - Goof (C++ Edition)

Thank you for your interest in contributing to this educational security project!

## Purpose

This repository is designed to demonstrate security vulnerabilities for educational purposes. Contributions should maintain this goal while improving the learning experience.

## How to Contribute

### 1. Reporting Issues

If you find:
- **Unintended vulnerabilities**: Please report them
- **Build issues**: Let us know about platform-specific problems
- **Documentation errors**: Help us improve clarity
- **Missing vulnerability examples**: Suggest new educational content

### 2. Suggesting Enhancements

We welcome suggestions for:
- Additional vulnerability examples
- Better documentation
- More comprehensive scanning examples
- Platform compatibility improvements
- Educational content enhancements

### 3. Pull Requests

When submitting a pull request:

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b feature/new-vulnerability-example
   ```
3. **Make your changes**
4. **Test your changes**
   - Ensure the code compiles on Linux, macOS, and Windows
   - Verify the vulnerability demonstrates as intended
   - Update documentation as needed
5. **Commit with clear messages**
   ```bash
   git commit -m "Add: Example of integer underflow vulnerability"
   ```
6. **Push to your fork**
   ```bash
   git push origin feature/new-vulnerability-example
   ```
7. **Open a Pull Request**

## Guidelines

### Code Contributions

- **Maintain educational value**: New vulnerabilities should be clear and educational
- **Add documentation**: Explain what the vulnerability is, why it's dangerous, and how to exploit it
- **Include CWE references**: Link to relevant CWE (Common Weakness Enumeration) entries
- **Keep it simple**: Code should be easy to understand for learners
- **Cross-platform**: Test on multiple platforms when possible
- **Comment clearly**: Mark vulnerable code sections clearly

### Example of Good Vulnerable Code

```cpp
// ============================================================================
// VULNERABILITY: Description (CWE-XXX)
// ============================================================================
void vulnerableFunction(const char* userInput) {
    // VULNERABLE: Explanation of why this is vulnerable
    // Dangerous code here
}
```

### Documentation Contributions

- Use clear, accessible language
- Include practical examples
- Provide remediation advice
- Link to relevant resources

### Types of Contributions We're Looking For

1. **New vulnerability examples**:
   - Additional CWE categories
   - Modern C++ specific vulnerabilities
   - Real-world inspired scenarios

2. **Platform support**:
   - Windows build improvements
   - macOS specific issues
   - Linux distribution compatibility

3. **Security tool integration**:
   - Examples with different SAST tools
   - SCA tool configurations
   - CI/CD pipeline examples

4. **Educational content**:
   - Workshop guides
   - Training materials
   - Video tutorials
   - Blog post examples

## Code of Conduct

### Be Respectful
- This is an educational project
- Be patient with learners and contributors
- Provide constructive feedback

### Be Responsible
- Remember this code is intentionally vulnerable
- Never encourage misuse of these techniques
- Promote ethical security practices

### Be Clear
- Explain security concepts thoroughly
- Use precise terminology
- Provide context for learners

## Review Process

1. Pull requests will be reviewed for:
   - Educational value
   - Code quality and clarity
   - Documentation completeness
   - Cross-platform compatibility
   - Security implications (both intended and unintended)

2. We may request changes to:
   - Improve clarity
   - Add documentation
   - Fix build issues
   - Enhance educational value

## Questions?

If you have questions about contributing:
- Open an issue with the "question" label
- Check existing issues for similar questions
- Review the README for project goals

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

## Acknowledgments

Contributors will be acknowledged in:
- The project README
- Release notes
- Workshop materials (with permission)

Thank you for helping make security education better!

