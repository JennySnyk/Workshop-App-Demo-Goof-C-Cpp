# Outputs for Workshop App Demo - Goof (C++ Edition)

output "instance_public_ip" {
  description = "Public IP of EC2 instance"
  value       = aws_instance.vulnerable_instance.public_ip
}

output "instance_id" {
  description = "ID of EC2 instance"
  value       = aws_instance.vulnerable_instance.id
}

# VULNERABILITY: Exposing sensitive information in outputs
output "db_endpoint" {
  description = "Database endpoint"
  value       = aws_db_instance.vulnerable_db.endpoint
}

output "db_password" {
  description = "Database password"
  value       = aws_db_instance.vulnerable_db.password  # VULNERABLE: Exposing password
  # Should be: sensitive = true
}

output "s3_bucket_name" {
  description = "S3 bucket name"
  value       = aws_s3_bucket.vulnerable_bucket.id
}

output "security_group_id" {
  description = "Security group ID"
  value       = aws_security_group.vulnerable_sg.id
}

