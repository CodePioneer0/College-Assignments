-- AJAX XAMPP Project Database Setup
-- Run this in phpMyAdmin or MySQL command line

-- Create database
CREATE DATABASE IF NOT EXISTS ajax_project;
USE ajax_project;

-- Create users table
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    phone VARCHAR(15) NOT NULL,
    city VARCHAR(50) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- Insert sample data
INSERT INTO users (name, email, phone, city) VALUES
('John Doe', 'john.doe@email.com', '1234567890', 'New York'),
('Jane Smith', 'jane.smith@email.com', '0987654321', 'Los Angeles'),
('Mike Johnson', 'mike.johnson@email.com', '5555666777', 'Chicago'),
('Sarah Wilson', 'sarah.wilson@email.com', '1111222333', 'Houston'),
('David Brown', 'david.brown@email.com', '9999888777', 'Phoenix');

-- Show the created table
SELECT * FROM users;