<?php
/**
 * Database Configuration File
 * XAMPP MySQL Connection using PDO
 */

// Database configuration
define('DB_HOST', 'localhost');
define('DB_NAME', 'ajax_project');
define('DB_USER', 'root');
define('DB_PASS', ''); // Default XAMPP MySQL password is empty

// PDO options for better error handling and security
$options = [
    PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
    PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
    PDO::ATTR_EMULATE_PREPARES => false,
];

try {
    // Create PDO connection
    $pdo = new PDO(
        "mysql:host=" . DB_HOST . ";dbname=" . DB_NAME . ";charset=utf8mb4",
        DB_USER,
        DB_PASS,
        $options
    );
    
    // Connection successful
    // echo "Database connected successfully";
    
} catch (PDOException $e) {
    // Connection failed
    die("Connection failed: " . $e->getMessage());
}

/**
 * Function to get database connection
 * @return PDO
 */
function getConnection() {
    global $pdo;
    return $pdo;
}

/**
 * Function to close database connection
 */
function closeConnection() {
    global $pdo;
    $pdo = null;
}

// Set content type for JSON responses
header('Content-Type: application/json');

// Allow CORS for AJAX requests
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS');
header('Access-Control-Allow-Headers: Content-Type, Authorization');

// Handle preflight requests
if ($_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
    http_response_code(204);
    exit();
}
?>