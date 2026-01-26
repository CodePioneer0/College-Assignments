<?php
header('Content-Type: application/json');
require_once 'config.php';

$action = $_POST['action'] ?? $_GET['action'] ?? '';

switch($action) {
    case 'fetch':
        fetchUsers($pdo);
        break;
    
    case 'add':
        addUser($pdo);
        break;
    
    case 'update':
        updateUser($pdo);
        break;
    
    case 'delete':
        deleteUser($pdo);
        break;
    
    default:
        echo json_encode(['success' => false, 'message' => 'Invalid action']);
}

function fetchUsers($pdo) {
    try {
        $stmt = $pdo->query("SELECT * FROM users ORDER BY id DESC");
        $users = $stmt->fetchAll();
        echo json_encode(['success' => true, 'data' => $users]);
    } catch(PDOException $e) {
        echo json_encode(['success' => false, 'message' => $e->getMessage()]);
    }
}

function addUser($pdo) {
    try {
        $name = $_POST['name'] ?? '';
        $email = $_POST['email'] ?? '';
        $phone = $_POST['phone'] ?? '';
        
        if(empty($name) || empty($email)) {
            echo json_encode(['success' => false, 'message' => 'Name and email are required']);
            return;
        }
        
        $stmt = $pdo->prepare("INSERT INTO users (name, email, phone) VALUES (?, ?, ?)");
        $stmt->execute([$name, $email, $phone]);
        
        echo json_encode(['success' => true, 'message' => 'User added successfully']);
    } catch(PDOException $e) {
        echo json_encode(['success' => false, 'message' => $e->getMessage()]);
    }
}

function updateUser($pdo) {
    try {
        $id = $_POST['id'] ?? '';
        $name = $_POST['name'] ?? '';
        $email = $_POST['email'] ?? '';
        $phone = $_POST['phone'] ?? '';
        
        if(empty($id) || empty($name) || empty($email)) {
            echo json_encode(['success' => false, 'message' => 'ID, name and email are required']);
            return;
        }
        
        $stmt = $pdo->prepare("UPDATE users SET name = ?, email = ?, phone = ? WHERE id = ?");
        $stmt->execute([$name, $email, $phone, $id]);
        
        echo json_encode(['success' => true, 'message' => 'User updated successfully']);
    } catch(PDOException $e) {
        echo json_encode(['success' => false, 'message' => $e->getMessage()]);
    }
}

function deleteUser($pdo) {
    try {
        $id = $_POST['id'] ?? '';
        
        if(empty($id)) {
            echo json_encode(['success' => false, 'message' => 'ID is required']);
            return;
        }
        
        $stmt = $pdo->prepare("DELETE FROM users WHERE id = ?");
        $stmt->execute([$id]);
        
        echo json_encode(['success' => true, 'message' => 'User deleted successfully']);
    } catch(PDOException $e) {
        echo json_encode(['success' => false, 'message' => $e->getMessage()]);
    }
}
?>