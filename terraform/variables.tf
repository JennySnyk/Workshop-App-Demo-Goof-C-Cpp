# Variables for Workshop App Demo - Goof (C++ Edition)

variable "aws_region" {
  description = "AWS region for resources"
  type        = string
  default     = "us-east-1"
}

variable "environment" {
  description = "Environment name"
  type        = string
  default     = "demo"
}

# VULNERABILITY: Sensitive default values exposed
variable "db_password" {
  description = "Database password"
  type        = string
  default     = "password123"  # VULNERABLE: Default password in code
  # Should be: sensitive = true
}

variable "api_key" {
  description = "API Key"
  type        = string
  default     = "sk_live_vulnerable_key"  # VULNERABLE: Hardcoded API key
  # Should be: sensitive = true
}

