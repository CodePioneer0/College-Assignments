<?php
// Set header to return JSON
header('Content-Type: application/json');

// Get action parameter
$action = $_GET['action'] ?? '';

// Check action and call function
if ($action === 'hello') {
    displayHelloPHP();
} elseif ($action === 'grade') {
    calculateGrade();
} elseif ($action === 'oddNumbers') {
    displayOddNumbers();
} elseif ($action === 'sortNumbers') {
    sortNumbers();
} elseif ($action === 'animals') {
    displayAnimals();
} elseif ($action === 'submitForm') {
    handleFormSubmission();
} elseif ($action === 'animalImages') {
    displayAnimalImages();
}

// Function to return "Hello PHP"
function displayHelloPHP() {
    echo json_encode([
        'message' => 'Hello PHP'
    ]);
}

// Function to calculate grade based on marks
function calculateGrade() {
    $marks = $_GET['marks'] ?? null;
    
    // Validate marks
    if ($marks === null || $marks === '') {
        echo json_encode([
            'error' => 'Marks parameter is required'
        ]);
        return;
    }
    
    $marks = floatval($marks);
    
    // Validate marks range
    if ($marks < 0 || $marks > 100) {
        echo json_encode([
            'error' => 'Marks must be between 0 and 100'
        ]);
        return;
    }
    
    // Determine grade based on marks
    $grade = '';
    if ($marks >= 90) {
        $grade = 'A+ (Outstanding)';
    } elseif ($marks >= 80) {
        $grade = 'A (Excellent)';
    } elseif ($marks >= 70) {
        $grade = 'B+ (Very Good)';
    } elseif ($marks >= 60) {
        $grade = 'B (Good)';
    } elseif ($marks >= 50) {
        $grade = 'C (Average)';
    } elseif ($marks >= 40) {
        $grade = 'D (Pass)';
    } else {
        $grade = 'F (Fail)';
    }
    
    echo json_encode([
        'marks' => $marks,
        'grade' => $grade
    ]);
}

// Function to display odd numbers from 1 to N
function displayOddNumbers() {
    $n = $_GET['n'] ?? null;
    
    // Validate N
    if ($n === null || $n === '') {
        echo json_encode([
            'error' => 'N parameter is required'
        ]);
        return;
    }
    
    $n = intval($n);
    
    // Validate N range
    if ($n < 1) {
        echo json_encode([
            'error' => 'N must be greater than 0'
        ]);
        return;
    }
    
    if ($n > 1000) {
        echo json_encode([
            'error' => 'N must be less than or equal to 1000'
        ]);
        return;
    }
    
    // Generate odd numbers from 1 to N
    $oddNumbers = [];
    for ($i = 1; $i <= $n; $i++) {
        if ($i % 2 != 0) {
            $oddNumbers[] = $i;
        }
    }
    
    echo json_encode([
        'n' => $n,
        'oddNumbers' => $oddNumbers,
        'count' => count($oddNumbers)
    ]);
}

// Function to sort N numbers using PHP array
function sortNumbers() {
    $numbersString = $_GET['numbers'] ?? null;
    
    // Validate input
    if ($numbersString === null || $numbersString === '') {
        echo json_encode([
            'error' => 'Numbers parameter is required'
        ]);
        return;
    }
    
    // Split the string by comma and convert to array
    $numbersArray = explode(',', $numbersString);
    
    // Clean and validate each number
    $cleanNumbers = [];
    foreach ($numbersArray as $num) {
        $num = trim($num); // Remove whitespace
        if (is_numeric($num)) {
            $cleanNumbers[] = floatval($num);
        }
    }
    
    // Check if we have valid numbers
    if (empty($cleanNumbers)) {
        echo json_encode([
            'error' => 'Please enter valid numbers separated by commas'
        ]);
        return;
    }
    
    // Store original array
    $originalNumbers = $cleanNumbers;
    
    // Sort the array in ascending order
    sort($cleanNumbers);
    
    echo json_encode([
        'original' => $originalNumbers,
        'sorted' => $cleanNumbers,
        'count' => count($cleanNumbers)
    ]);
}

// Function to display N animal names using PHP array
function displayAnimals() {
    $n = $_GET['n'] ?? null;
    
    // Validate N
    if ($n === null || $n === '') {
        echo json_encode([
            'error' => 'N parameter is required'
        ]);
        return;
    }
    
    $n = intval($n);
    
    // Validate N range
    if ($n < 1) {
        echo json_encode([
            'error' => 'N must be greater than 0'
        ]);
        return;
    }
    
    if ($n > 50) {
        echo json_encode([
            'error' => 'N must be less than or equal to 50'
        ]);
        return;
    }
    
    // Array of animal names
    $allAnimals = [
        'Lion', 'Tiger', 'Elephant', 'Giraffe', 'Zebra',
        'Panda', 'Koala', 'Kangaroo', 'Penguin', 'Dolphin',
        'Eagle', 'Owl', 'Parrot', 'Peacock', 'Flamingo',
        'Monkey', 'Gorilla', 'Chimpanzee', 'Orangutan', 'Lemur',
        'Bear', 'Wolf', 'Fox', 'Deer', 'Moose',
        'Rhinoceros', 'Hippopotamus', 'Crocodile', 'Alligator', 'Snake',
        'Turtle', 'Tortoise', 'Frog', 'Salamander', 'Chameleon',
        'Butterfly', 'Bee', 'Ant', 'Dragonfly', 'Ladybug',
        'Shark', 'Whale', 'Octopus', 'Jellyfish', 'Starfish',
        'Rabbit', 'Squirrel', 'Hedgehog', 'Hamster', 'Guinea Pig'
    ];
    
    // Get first N animals from the array using array_slice
    $selectedAnimals = array_slice($allAnimals, 0, $n);
    
    echo json_encode([
        'n' => $n,
        'animals' => $selectedAnimals
    ]);
}

// Function to handle form submission with various form elements
function handleFormSubmission() {
    // Get all form parameters
    $username = $_GET['username'] ?? '';
    $password = $_GET['password'] ?? '';
    $gender = $_GET['gender'] ?? '';
    $country = $_GET['country'] ?? '';
    $fileName = $_GET['fileName'] ?? '';
    $fileSize = $_GET['fileSize'] ?? 0;
    $hiddenField = $_GET['hiddenField'] ?? '';
    $timestamp = $_GET['timestamp'] ?? '';
    
    // Validate required fields
    if (empty($username) || empty($password) || empty($gender) || empty($country)) {
        echo json_encode([
            'error' => 'All required fields must be filled'
        ]);
        return;
    }
    
    // Mask password for security (show only asterisks)
    $passwordMask = str_repeat('*', strlen($password));
    
    // Prepare response with all form element data
    echo json_encode([
        'success' => true,
        'username' => $username,
        'passwordMask' => $passwordMask,
        'gender' => $gender,
        'country' => $country,
        'fileName' => $fileName,
        'fileSize' => (int)$fileSize,
        'hiddenField' => $hiddenField,
        'timestamp' => $timestamp,
        'message' => 'Form submitted successfully with all elements!'
    ]);
}

// Function to display N animal images using PHP array
function displayAnimalImages() {
    $n = $_GET['n'] ?? null;
    
    // Validate N
    if ($n === null || $n === '') {
        echo json_encode([
            'error' => 'N parameter is required'
        ]);
        return;
    }
    
    $n = intval($n);
    
    // Validate N range
    if ($n < 1) {
        echo json_encode([
            'error' => 'N must be greater than 0'
        ]);
        return;
    }
    
    if ($n > 20) {
        echo json_encode([
            'error' => 'N must be less than or equal to 20'
        ]);
        return;
    }
    
    // Array of animals with their image URLs (using placeholder images)
    $animalImages = [
        [
            'name' => 'Lion',
            'imageUrl' => 'https://images.unsplash.com/photo-1546182990-dffeafbe841d?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Tiger',
            'imageUrl' => 'https://images.unsplash.com/photo-1561731216-c3a4d99437d5?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Elephant',
            'imageUrl' => 'https://images.unsplash.com/photo-1564760055775-d63b17a55c44?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Giraffe',
            'imageUrl' => 'https://images.unsplash.com/photo-1547721064-da6cfb341d50?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Zebra',
            'imageUrl' => 'https://images.unsplash.com/photo-1523805009345-7448845a9e53?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Panda',
            'imageUrl' => 'https://images.unsplash.com/photo-1564349683136-77e08dba1ef7?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Koala',
            'imageUrl' => 'https://images.unsplash.com/photo-1459262838948-3e2de6c1ec80?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Penguin',
            'imageUrl' => 'https://images.unsplash.com/photo-1551986782-d0169b3f8fa7?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Dolphin',
            'imageUrl' => 'https://images.unsplash.com/photo-1607153333879-c174d265f1d2?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Eagle',
            'imageUrl' => 'https://images.unsplash.com/photo-1611689037241-d8dfe4280f2e?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Owl',
            'imageUrl' => 'https://images.unsplash.com/photo-1568393691622-c7ba131d63b4?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Parrot',
            'imageUrl' => 'https://images.unsplash.com/photo-1552728089-57bdde30beb3?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Monkey',
            'imageUrl' => 'https://images.unsplash.com/photo-1540573133985-87b6da6d54a9?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Bear',
            'imageUrl' => 'https://images.unsplash.com/photo-1589656966895-2f33e7653819?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Wolf',
            'imageUrl' => 'https://images.unsplash.com/photo-1614027164847-1b28cfe1df60?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Fox',
            'imageUrl' => 'https://images.unsplash.com/photo-1474511320723-9a56873867b5?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Deer',
            'imageUrl' => 'https://images.unsplash.com/photo-1551892374-ecf8875e9254?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Rabbit',
            'imageUrl' => 'https://images.unsplash.com/photo-1585110396000-c9ffd4e4b308?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Squirrel',
            'imageUrl' => 'https://images.unsplash.com/photo-1553201244-d986cf223293?w=400&h=300&fit=crop'
        ],
        [
            'name' => 'Hedgehog',
            'imageUrl' => 'https://images.unsplash.com/photo-1584673629042-c5a0da9d6e39?w=400&h=300&fit=crop'
        ]
    ];
    
    // Get first N animals from the array using array_slice
    $selectedAnimals = array_slice($animalImages, 0, $n);
    
    echo json_encode([
        'n' => $n,
        'animals' => $selectedAnimals
    ]);
}
?>