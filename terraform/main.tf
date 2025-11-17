# Workshop App Demo - Goof (C++ Edition)
# Deliberately Vulnerable Terraform Configuration
# DO NOT USE IN PRODUCTION

terraform {
  required_version = ">= 1.0"
  
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 4.0"
    }
  }
}

provider "aws" {
  region = var.aws_region
}

# VULNERABILITY: S3 bucket with public access
resource "aws_s3_bucket" "vulnerable_bucket" {
  bucket = "goof-cpp-demo-bucket-${random_string.suffix.result}"
  
  tags = {
    Name        = "Goof C++ Demo Bucket"
    Environment = "Demo"
  }
}

# VULNERABILITY: Public ACL enabled
resource "aws_s3_bucket_acl" "vulnerable_bucket_acl" {
  bucket = aws_s3_bucket.vulnerable_bucket.id
  acl    = "public-read"  # VULNERABLE: Public read access
}

# VULNERABILITY: No encryption enabled
resource "aws_s3_bucket_server_side_encryption_configuration" "vulnerable_encryption" {
  bucket = aws_s3_bucket.vulnerable_bucket.id

  rule {
    apply_server_side_encryption_by_default {
      sse_algorithm = "AES256"
      # VULNERABLE: Not using KMS encryption
    }
  }
}

# VULNERABILITY: Versioning disabled
resource "aws_s3_bucket_versioning" "vulnerable_versioning" {
  bucket = aws_s3_bucket.vulnerable_bucket.id
  
  versioning_configuration {
    status = "Disabled"  # VULNERABLE: No versioning
  }
}

# VULNERABILITY: Security group with overly permissive rules
resource "aws_security_group" "vulnerable_sg" {
  name        = "goof-cpp-vulnerable-sg"
  description = "Vulnerable security group for demo"
  vpc_id      = aws_vpc.main.id

  # VULNERABLE: Open to the world on all ports
  ingress {
    from_port   = 0
    to_port     = 65535
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]  # VULNERABLE: Open to internet
    description = "Allow all inbound traffic"
  }

  # VULNERABLE: SSH open to the world
  ingress {
    from_port   = 22
    to_port     = 22
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]  # VULNERABLE: SSH open to internet
    description = "SSH from anywhere"
  }

  # VULNERABLE: Database port open to the world
  ingress {
    from_port   = 3306
    to_port     = 3306
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]  # VULNERABLE: MySQL open to internet
    description = "MySQL from anywhere"
  }

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    Name = "Goof C++ Vulnerable SG"
  }
}

# VULNERABILITY: EC2 instance with multiple issues
resource "aws_instance" "vulnerable_instance" {
  ami           = data.aws_ami.ubuntu.id
  instance_type = "t2.micro"
  
  vpc_security_group_ids = [aws_security_group.vulnerable_sg.id]
  subnet_id              = aws_subnet.public.id
  
  # VULNERABLE: No encryption for root volume
  root_block_device {
    volume_type           = "gp2"
    volume_size           = 20
    encrypted             = false  # VULNERABLE: Unencrypted volume
    delete_on_termination = true
  }

  # VULNERABLE: IMDSv1 enabled (allows SSRF attacks)
  metadata_options {
    http_endpoint               = "enabled"
    http_tokens                 = "optional"  # VULNERABLE: Should be "required" for IMDSv2
    http_put_response_hop_limit = 1
  }

  # VULNERABLE: Detailed monitoring disabled
  monitoring = false

  # VULNERABLE: Hardcoded sensitive data in user_data
  user_data = <<-EOF
              #!/bin/bash
              export DB_PASSWORD="SuperSecret123!"
              export API_KEY="sk_live_vulnerable_key_12345"
              echo "DB_PASSWORD=SuperSecret123!" >> /etc/environment
              apt-get update
              apt-get install -y docker.io
              EOF

  tags = {
    Name = "Goof C++ Vulnerable Instance"
  }
}

# VULNERABILITY: RDS instance with multiple issues
resource "aws_db_instance" "vulnerable_db" {
  identifier        = "goof-cpp-vulnerable-db"
  engine            = "mysql"
  engine_version    = "5.7"  # VULNERABLE: Older version
  instance_class    = "db.t2.micro"
  allocated_storage = 20

  db_name  = "goofdb"
  username = "admin"  # VULNERABLE: Default username
  password = "password123"  # VULNERABLE: Weak password in code

  # VULNERABLE: Publicly accessible database
  publicly_accessible = true

  # VULNERABLE: No encryption
  storage_encrypted = false

  # VULNERABLE: Backup retention too short
  backup_retention_period = 0

  # VULNERABLE: Skip final snapshot
  skip_final_snapshot = true

  # VULNERABLE: No deletion protection
  deletion_protection = false

  # VULNERABLE: Auto minor version upgrade disabled
  auto_minor_version_upgrade = false

  vpc_security_group_ids = [aws_security_group.vulnerable_sg.id]
  db_subnet_group_name   = aws_db_subnet_group.main.name

  tags = {
    Name = "Goof C++ Vulnerable DB"
  }
}

# VPC Configuration
resource "aws_vpc" "main" {
  cidr_block           = "10.0.0.0/16"
  enable_dns_hostnames = true
  enable_dns_support   = true

  tags = {
    Name = "Goof C++ VPC"
  }
}

resource "aws_subnet" "public" {
  vpc_id                  = aws_vpc.main.id
  cidr_block              = "10.0.1.0/24"
  availability_zone       = "${var.aws_region}a"
  map_public_ip_on_launch = true  # VULNERABLE: Auto-assign public IPs

  tags = {
    Name = "Goof C++ Public Subnet"
  }
}

resource "aws_subnet" "private" {
  vpc_id            = aws_vpc.main.id
  cidr_block        = "10.0.2.0/24"
  availability_zone = "${var.aws_region}b"

  tags = {
    Name = "Goof C++ Private Subnet"
  }
}

resource "aws_db_subnet_group" "main" {
  name       = "goof-cpp-db-subnet-group"
  subnet_ids = [aws_subnet.public.id, aws_subnet.private.id]

  tags = {
    Name = "Goof C++ DB Subnet Group"
  }
}

resource "aws_internet_gateway" "main" {
  vpc_id = aws_vpc.main.id

  tags = {
    Name = "Goof C++ IGW"
  }
}

resource "aws_route_table" "public" {
  vpc_id = aws_vpc.main.id

  route {
    cidr_block = "0.0.0.0/0"
    gateway_id = aws_internet_gateway.main.id
  }

  tags = {
    Name = "Goof C++ Public Route Table"
  }
}

resource "aws_route_table_association" "public" {
  subnet_id      = aws_subnet.public.id
  route_table_id = aws_route_table.public.id
}

# Data sources
data "aws_ami" "ubuntu" {
  most_recent = true
  owners      = ["099720109477"]  # Canonical

  filter {
    name   = "name"
    values = ["ubuntu/images/hvm-ssd/ubuntu-focal-20.04-amd64-server-*"]
  }

  filter {
    name   = "virtualization-type"
    values = ["hvm"]
  }
}

resource "random_string" "suffix" {
  length  = 8
  special = false
  upper   = false
}

