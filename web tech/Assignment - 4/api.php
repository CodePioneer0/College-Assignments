<?php
/**
 * AJAX API Endpoints for User Management
 * Handles all CRUD operations via AJAX
 */

require_once 'config.php';

// Get the request method and action
$method = $_SERVER['REQUEST_METHOD'];
$action = isset($_GET['action']) ? $_GET['action'] : '';

try {
    switch ($method) {
        case 'GET':
            if ($action === 'getUsers') {
                getUsers();
            } elseif ($action === 'getUser') {
                getUser();
            } else {
                sendResponse(['error' => 'Invalid GET action'], 400);
            }
            break;
            
        case 'POST':
            if ($action === 'createUser') {
                createUser();
            } else {
                sendResponse(['error' => 'Invalid POST action'], 400);
            }
            break;
            
        case 'PUT':
            if ($action === 'updateUser') {
                updateUser();
            } else {
                sendResponse(['error' => 'Invalid PUT action'], 400);
            }
            break;
            
        case 'DELETE':
            if ($action === 'deleteUser') {
                deleteUser();
            } else {
                sendResponse(['error' => 'Invalid DELETE action'], 400);
            }
            break;
            
        default:
            sendResponse(['error' => 'Method not allowed'], 405);
    }
} catch (Exception $e) {
    sendResponse(['error' => 'Server error: ' . $e->getMessage()], 500);
}

/**
 * Get all users
 */
function getUsers() {
    $pdo = getConnection();
    
    try {
        $stmt = $pdo->query("SELECT * FROM users ORDER BY created_at DESC");
        $users = $stmt->fetchAll();
        
        sendResponse([
            'success' => true,
            'data' => $users,
            'count' => count($users)
        ]);
    } catch (PDOException $e) {
        sendResponse(['error' => 'Database error: ' . $e->getMessage()], 500);
    }
}

/**
 * Get single user by ID
 */
function getUser() {
    $userId = isset($_GET['id']) ? intval($_GET['id']) : 0;
    
    if ($userId <= 0) {
        sendResponse(['error' => 'Invalid user ID'], 400);
        return;
    }
    
    $pdo = getConnection();
    
    try {
        $stmt = $pdo->prepare("SELECT * FROM users WHERE id = ?");
        $stmt->execute([$userId]);
        $user = $stmt->fetch();
        
        if ($user) {
            sendResponse([
                'success' => true,
                'data' => $user
            ]);
        } else {
            sendResponse(['error' => 'User not found'], 404);
        }
    } catch (PDOException $e) {
        sendResponse(['error' => 'Database error: ' . $e->getMessage()], 500);
    }
}

/**
 * Create new user
 */
function createUser() {
    $input = json_decode(file_get_contents('php://input'), true);
    
    // Validate required fields
    $required = ['name', 'email', 'phone', 'city'];
    foreach ($required as $field) {
        if (empty($input[$field])) {
            sendResponse(['error' => "Field '$field' is required"], 400);
            return;
        }
    }
    
    // Validate email format
    if (!filter_var($input['email'], FILTER_VALIDATE_EMAIL)) {
        sendResponse(['error' => 'Invalid email format'], 400);
        return;
    }
    
    $pdo = getConnection();
    
    try {
        // Check if email already exists
        $stmt = $pdo->prepare("SELECT COUNT(*) FROM users WHERE email = ?");
        $stmt->execute([$input['email']]);
        $exists = $stmt->fetchColumn();
        
        if ($exists > 0) {
            sendResponse(['error' => 'Email already exists'], 409);
            return;
        }
        
        // Insert new user
        $stmt = $pdo->prepare("INSERT INTO users (name, email, phone, city) VALUES (?, ?, ?, ?)");
        $stmt->execute([
            $input['name'],
            $input['email'],
            $input['phone'],
            $input['city']
        ]);
        
        $userId = $pdo->lastInsertId();
        
        sendResponse([
            'success' => true,
            'message' => 'User created successfully',
            'data' => ['id' => $userId]
        ], 201);
        
    } catch (PDOException $e) {
        sendResponse(['error' => 'Database error: ' . $e->getMessage()], 500);
    }
}

/**
 * Update existing user
 */
function updateUser() {
    $input = json_decode(file_get_contents('php://input'), true);
    
    // Validate user ID
    if (empty($input['id']) || !is_numeric($input['id'])) {
        sendResponse(['error' => 'Valid user ID is required'], 400);
        return;
    }
    
    $userId = intval($input['id']);
    
    // Validate required fields
    $required = ['name', 'email', 'phone', 'city'];
    foreach ($required as $field) {
        if (empty($input[$field])) {
            sendResponse(['error' => "Field '$field' is required"], 400);
            return;
        }
    }
    
    // Validate email format
    if (!filter_var($input['email'], FILTER_VALIDATE_EMAIL)) {
        sendResponse(['error' => 'Invalid email format'], 400);
        return;
    }
    
    $pdo = getConnection();
    
    try {
        // Check if user exists
        $stmt = $pdo->prepare("SELECT COUNT(*) FROM users WHERE id = ?");
        $stmt->execute([$userId]);
        $exists = $stmt->fetchColumn();
        
        if ($exists == 0) {
            sendResponse(['error' => 'User not found'], 404);
            return;
        }
        
        // Check if email exists for another user
        $stmt = $pdo->prepare("SELECT COUNT(*) FROM users WHERE email = ? AND id != ?");
        $stmt->execute([$input['email'], $userId]);
        $emailExists = $stmt->fetchColumn();
        
        if ($emailExists > 0) {
            sendResponse(['error' => 'Email already exists for another user'], 409);
            return;
        }
        
        // Update user
        $stmt = $pdo->prepare("UPDATE users SET name = ?, email = ?, phone = ?, city = ? WHERE id = ?");
        $stmt->execute([
            $input['name'],
            $input['email'],
            $input['phone'],
            $input['city'],
            $userId
        ]);
        
        sendResponse([
            'success' => true,
            'message' => 'User updated successfully'
        ]);
        
    } catch (PDOException $e) {
        sendResponse(['error' => 'Database error: ' . $e->getMessage()], 500);
    }
}

/**
 * Delete user
 */
function deleteUser() {
    $userId = isset($_GET['id']) ? intval($_GET['id']) : 0;
    
    if ($userId <= 0) {
        sendResponse(['error' => 'Invalid user ID'], 400);
        return;
    }
    
    $pdo = getConnection();
    
    try {
        // Check if user exists
        $stmt = $pdo->prepare("SELECT COUNT(*) FROM users WHERE id = ?");
        $stmt->execute([$userId]);
        $exists = $stmt->fetchColumn();
        
        if ($exists == 0) {
            sendResponse(['error' => 'User not found'], 404);
            return;
        }
        
        // Delete user
        $stmt = $pdo->prepare("DELETE FROM users WHERE id = ?");
        $stmt->execute([$userId]);
        
        sendResponse([
            'success' => true,
            'message' => 'User deleted successfully'
        ]);
        
    } catch (PDOException $e) {
        sendResponse(['error' => 'Database error: ' . $e->getMessage()], 500);
    }
}

/**
 * Send JSON response
 */
function sendResponse($data, $statusCode = 200) {
    http_response_code($statusCode);
    echo json_encode($data);
    exit();
}
?>