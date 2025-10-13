/**
 * AJAX User Management System - JavaScript
 * Handles all AJAX operations and DOM manipulation
 */

// Global variables
let currentEditingId = null;
let usersData = [];

// DOM elements
const userForm = document.getElementById('userForm');
const formTitle = document.getElementById('formTitle');
const submitBtn = document.getElementById('submitBtn');
const cancelBtn = document.getElementById('cancelBtn');
const usersTableBody = document.getElementById('usersTableBody');
const searchInput = document.getElementById('searchInput');
const refreshBtn = document.getElementById('refreshBtn');
const userCount = document.getElementById('userCount');
const alertContainer = document.getElementById('alertContainer');
const loadingOverlay = document.getElementById('loadingOverlay');
const confirmModal = document.getElementById('confirmModal');
const confirmMessage = document.getElementById('confirmMessage');
const confirmYes = document.getElementById('confirmYes');
const confirmNo = document.getElementById('confirmNo');

// Initialize the application
document.addEventListener('DOMContentLoaded', function() {
    initializeApp();
});

/**
 * Initialize the application
 */
function initializeApp() {
    loadUsers();
    bindEvents();
    showAlert('Application loaded successfully!', 'success', 3000);
}

/**
 * Bind event listeners
 */
function bindEvents() {
    // Form submission
    userForm.addEventListener('submit', handleFormSubmit);
    
    // Cancel button
    cancelBtn.addEventListener('click', resetForm);
    
    // Search functionality
    searchInput.addEventListener('input', handleSearch);
    
    // Refresh button
    refreshBtn.addEventListener('click', loadUsers);
    
    // Modal buttons
    confirmNo.addEventListener('click', hideConfirmModal);
    
    // Close modal on outside click
    confirmModal.addEventListener('click', function(e) {
        if (e.target === confirmModal) {
            hideConfirmModal();
        }
    });
    
    // Auto-hide alerts
    alertContainer.addEventListener('click', function(e) {
        if (e.target.classList.contains('alert-close')) {
            e.target.parentElement.remove();
        }
    });
}

/**
 * Handle form submission
 */
async function handleFormSubmit(e) {
    e.preventDefault();
    
    const formData = new FormData(userForm);
    const userData = Object.fromEntries(formData.entries());
    
    // Validate form data
    if (!validateFormData(userData)) {
        return;
    }
    
    try {
        showLoading(true);
        
        if (currentEditingId) {
            // Update existing user
            userData.id = currentEditingId;
            await updateUser(userData);
        } else {
            // Create new user
            await createUser(userData);
        }
        
        resetForm();
        loadUsers();
        
    } catch (error) {
        showAlert('Error: ' + error.message, 'error');
    } finally {
        showLoading(false);
    }
}

/**
 * Validate form data
 */
function validateFormData(data) {
    const errors = [];
    
    // Name validation
    if (!data.name || data.name.trim().length < 2) {
        errors.push('Name must be at least 2 characters long');
    }
    
    // Email validation
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!data.email || !emailRegex.test(data.email)) {
        errors.push('Please enter a valid email address');
    }
    
    // Phone validation
    const phoneRegex = /^[\d\-\+\(\)\s]+$/;
    if (!data.phone || !phoneRegex.test(data.phone) || data.phone.length < 10) {
        errors.push('Please enter a valid phone number');
    }
    
    // City validation
    if (!data.city || data.city.trim().length < 2) {
        errors.push('City must be at least 2 characters long');
    }
    
    if (errors.length > 0) {
        showAlert(errors.join('<br>'), 'error');
        return false;
    }
    
    return true;
}

/**
 * Load all users via AJAX
 */
async function loadUsers() {
    try {
        showLoading(true);
        
        const response = await fetch('api.php?action=getUsers');
        const result = await response.json();
        
        if (result.success) {
            usersData = result.data;
            displayUsers(usersData);
            updateUserCount(result.count);
        } else {
            throw new Error(result.error || 'Failed to load users');
        }
        
    } catch (error) {
        showAlert('Error loading users: ' + error.message, 'error');
        displayUsers([]);
        updateUserCount(0);
    } finally {
        showLoading(false);
    }
}

/**
 * Create new user via AJAX
 */
async function createUser(userData) {
    const response = await fetch('api.php?action=createUser', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(userData)
    });
    
    const result = await response.json();
    
    if (result.success) {
        showAlert('User created successfully!', 'success');
    } else {
        throw new Error(result.error || 'Failed to create user');
    }
}

/**
 * Update user via AJAX
 */
async function updateUser(userData) {
    const response = await fetch('api.php?action=updateUser', {
        method: 'PUT',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(userData)
    });
    
    const result = await response.json();
    
    if (result.success) {
        showAlert('User updated successfully!', 'success');
    } else {
        throw new Error(result.error || 'Failed to update user');
    }
}

/**
 * Delete user via AJAX
 */
async function deleteUser(userId) {
    const response = await fetch(`api.php?action=deleteUser&id=${userId}`, {
        method: 'DELETE'
    });
    
    const result = await response.json();
    
    if (result.success) {
        showAlert('User deleted successfully!', 'success');
        loadUsers();
    } else {
        throw new Error(result.error || 'Failed to delete user');
    }
}

/**
 * Display users in table
 */
function displayUsers(users) {
    if (users.length === 0) {
        usersTableBody.innerHTML = `
            <tr>
                <td colspan="7" class="no-users">
                    <i class="fas fa-users"></i><br>
                    No users found. Add some users to get started!
                </td>
            </tr>
        `;
        return;
    }
    
    usersTableBody.innerHTML = users.map(user => `
        <tr data-user-id="${user.id}">
            <td>${user.id}</td>
            <td>${escapeHtml(user.name)}</td>
            <td>${escapeHtml(user.email)}</td>
            <td>${escapeHtml(user.phone)}</td>
            <td>${escapeHtml(user.city)}</td>
            <td>${formatDate(user.created_at)}</td>
            <td>
                <div class="action-buttons">
                    <button class="btn btn-edit btn-sm" onclick="editUser(${user.id})" title="Edit User">
                        <i class="fas fa-edit"></i> Edit
                    </button>
                    <button class="btn btn-delete btn-sm" onclick="confirmDeleteUser(${user.id}, '${escapeHtml(user.name)}')" title="Delete User">
                        <i class="fas fa-trash"></i> Delete
                    </button>
                </div>
            </td>
        </tr>
    `).join('');
}

/**
 * Edit user - populate form
 */
async function editUser(userId) {
    try {
        showLoading(true);
        
        const response = await fetch(`api.php?action=getUser&id=${userId}`);
        const result = await response.json();
        
        if (result.success) {
            const user = result.data;
            
            // Populate form
            document.getElementById('userId').value = user.id;
            document.getElementById('userName').value = user.name;
            document.getElementById('userEmail').value = user.email;
            document.getElementById('userPhone').value = user.phone;
            document.getElementById('userCity').value = user.city;
            
            // Update form state
            currentEditingId = userId;
            formTitle.innerHTML = '<i class="fas fa-user-edit"></i> Edit User';
            submitBtn.innerHTML = '<i class="fas fa-save"></i> Update User';
            cancelBtn.style.display = 'inline-flex';
            
            // Scroll to form
            document.querySelector('.form-container').scrollIntoView({ 
                behavior: 'smooth' 
            });
            
            showAlert('User loaded for editing', 'success');
            
        } else {
            throw new Error(result.error || 'Failed to load user');
        }
        
    } catch (error) {
        showAlert('Error loading user: ' + error.message, 'error');
    } finally {
        showLoading(false);
    }
}

/**
 * Confirm delete user
 */
function confirmDeleteUser(userId, userName) {
    confirmMessage.innerHTML = `
        Are you sure you want to delete user <strong>"${escapeHtml(userName)}"</strong>?<br>
        <small class="text-muted">This action cannot be undone.</small>
    `;
    
    confirmYes.onclick = function() {
        hideConfirmModal();
        performDeleteUser(userId);
    };
    
    showConfirmModal();
}

/**
 * Perform delete user
 */
async function performDeleteUser(userId) {
    try {
        showLoading(true);
        await deleteUser(userId);
    } catch (error) {
        showAlert('Error deleting user: ' + error.message, 'error');
    } finally {
        showLoading(false);
    }
}

/**
 * Reset form to initial state
 */
function resetForm() {
    userForm.reset();
    currentEditingId = null;
    
    // Reset form appearance
    formTitle.innerHTML = '<i class="fas fa-user-plus"></i> Add New User';
    submitBtn.innerHTML = '<i class="fas fa-save"></i> Save User';
    cancelBtn.style.display = 'none';
    
    // Clear any field errors
    const inputs = userForm.querySelectorAll('input');
    inputs.forEach(input => {
        input.classList.remove('error');
    });
}

/**
 * Handle search functionality
 */
function handleSearch() {
    const searchTerm = searchInput.value.toLowerCase().trim();
    
    if (searchTerm === '') {
        displayUsers(usersData);
        updateUserCount(usersData.length);
        return;
    }
    
    const filteredUsers = usersData.filter(user => 
        user.name.toLowerCase().includes(searchTerm) ||
        user.email.toLowerCase().includes(searchTerm) ||
        user.city.toLowerCase().includes(searchTerm) ||
        user.phone.includes(searchTerm)
    );
    
    displayUsers(filteredUsers);
    updateUserCount(filteredUsers.length, usersData.length);
}

/**
 * Update user count display
 */
function updateUserCount(count, total = null) {
    if (total !== null && total !== count) {
        userCount.textContent = `Showing ${count} of ${total} users`;
    } else {
        userCount.textContent = `${count} ${count === 1 ? 'user' : 'users'}`;
    }
}

/**
 * Show alert message
 */
function showAlert(message, type = 'success', duration = 5000) {
    const alertDiv = document.createElement('div');
    alertDiv.className = `alert alert-${type}`;
    alertDiv.innerHTML = `
        ${message}
        <button class="alert-close" type="button">&times;</button>
    `;
    
    alertContainer.appendChild(alertDiv);
    
    // Auto-remove alert after duration
    if (duration > 0) {
        setTimeout(() => {
            if (alertDiv.parentElement) {
                alertDiv.remove();
            }
        }, duration);
    }
}

/**
 * Show/hide loading overlay
 */
function showLoading(show) {
    loadingOverlay.style.display = show ? 'flex' : 'none';
}

/**
 * Show confirmation modal
 */
function showConfirmModal() {
    confirmModal.style.display = 'flex';
    document.body.style.overflow = 'hidden';
}

/**
 * Hide confirmation modal
 */
function hideConfirmModal() {
    confirmModal.style.display = 'none';
    document.body.style.overflow = 'auto';
}

/**
 * Escape HTML to prevent XSS
 */
function escapeHtml(text) {
    const map = {
        '&': '&amp;',
        '<': '&lt;',
        '>': '&gt;',
        '"': '&quot;',
        "'": '&#039;'
    };
    return text.replace(/[&<>"']/g, function(m) { return map[m]; });
}

/**
 * Format date for display
 */
function formatDate(dateString) {
    const date = new Date(dateString);
    return date.toLocaleDateString('en-US', {
        year: 'numeric',
        month: 'short',
        day: '2-digit',
        hour: '2-digit',
        minute: '2-digit'
    });
}

/**
 * Utility function for API calls with error handling
 */
async function apiCall(url, options = {}) {
    try {
        const response = await fetch(url, {
            headers: {
                'Content-Type': 'application/json',
                ...options.headers
            },
            ...options
        });
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        const result = await response.json();
        
        if (!result.success && result.error) {
            throw new Error(result.error);
        }
        
        return result;
        
    } catch (error) {
        if (error.name === 'TypeError' && error.message.includes('fetch')) {
            throw new Error('Network error. Please check your connection and try again.');
        }
        throw error;
    }
}

/**
 * Export data as JSON (bonus feature)
 */
function exportData() {
    const dataStr = JSON.stringify(usersData, null, 2);
    const dataBlob = new Blob([dataStr], {type: 'application/json'});
    
    const link = document.createElement('a');
    link.href = URL.createObjectURL(dataBlob);
    link.download = `users_export_${new Date().toISOString().split('T')[0]}.json`;
    link.click();
    
    showAlert('Data exported successfully!', 'success');
}

/**
 * Keyboard shortcuts
 */
document.addEventListener('keydown', function(e) {
    // Escape key to cancel editing
    if (e.key === 'Escape') {
        if (confirmModal.style.display === 'flex') {
            hideConfirmModal();
        } else if (currentEditingId) {
            resetForm();
        }
    }
    
    // Ctrl+R to refresh
    if (e.ctrlKey && e.key === 'r') {
        e.preventDefault();
        loadUsers();
    }
    
    // Ctrl+F to focus search
    if (e.ctrlKey && e.key === 'f') {
        e.preventDefault();
        searchInput.focus();
    }
});

// Add some additional features for better UX
document.addEventListener('DOMContentLoaded', function() {
    // Add loading states to buttons
    const buttons = document.querySelectorAll('.btn');
    buttons.forEach(button => {
        button.addEventListener('click', function() {
            if (!button.disabled) {
                const originalText = button.innerHTML;
                button.disabled = true;
                
                setTimeout(() => {
                    button.disabled = false;
                }, 1000);
            }
        });
    });
    
    // Add form validation feedback
    const inputs = userForm.querySelectorAll('input[required]');
    inputs.forEach(input => {
        input.addEventListener('blur', function() {
            if (this.value.trim() === '') {
                this.style.borderColor = '#e74c3c';
            } else {
                this.style.borderColor = '#27ae60';
            }
        });
        
        input.addEventListener('input', function() {
            if (this.style.borderColor === 'rgb(231, 76, 60)') {
                this.style.borderColor = '#e0e6ed';
            }
        });
    });
});