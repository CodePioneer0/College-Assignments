// External JavaScript file using document.write() to create entire HTML page
// report-generator.js

function generateStudentReport() {
    // CSS styles for the page
    document.write(`
        <style>
            * {
                margin: 0;
                padding: 0;
                box-sizing: border-box;
            }
            
            body {
                font-family: 'Arial', sans-serif;
                line-height: 1.6;
                background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);
                min-height: 100vh;
                color: #333;
            }
            
            .container {
                max-width: 900px;
                margin: 0 auto;
                padding: 20px;
                background: white;
                min-height: 100vh;
                box-shadow: 0 0 20px rgba(0,0,0,0.1);
            }
            
            .header {
                text-align: center;
                border-bottom: 3px solid #2c3e50;
                padding-bottom: 20px;
                margin-bottom: 30px;
            }
            
            .university-logo {
                width: 80px;
                height: 80px;
                background: #2c3e50;
                border-radius: 50%;
                margin: 0 auto 15px;
                display: flex;
                align-items: center;
                justify-content: center;
                color: white;
                font-size: 24px;
                font-weight: bold;
            }
            
            .university-name {
                font-size: 24px;
                font-weight: bold;
                color: #2c3e50;
                margin-bottom: 5px;
            }
            
            .department {
                font-size: 16px;
                color: #34495e;
                margin-bottom: 10px;
            }
            
            .report-title {
                font-size: 20px;
                color: #e74c3c;
                font-weight: bold;
                text-transform: uppercase;
                letter-spacing: 1px;
            }
            
            .student-info {
                background: #f8f9fa;
                padding: 20px;
                border-radius: 10px;
                margin-bottom: 25px;
                border-left: 5px solid #3498db;
            }
            
            .info-row {
                display: flex;
                margin-bottom: 10px;
            }
            
            .info-label {
                font-weight: bold;
                width: 150px;
                color: #2c3e50;
            }
            
            .info-value {
                color: #34495e;
            }
            
            .semester-table {
                width: 100%;
                border-collapse: collapse;
                margin-bottom: 25px;
                background: white;
                border-radius: 8px;
                overflow: hidden;
                box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            }
            
            .semester-table th {
                background: #3498db;
                color: white;
                padding: 15px;
                text-align: left;
                font-weight: bold;
            }
            
            .semester-table td {
                padding: 12px 15px;
                border-bottom: 1px solid #ecf0f1;
            }
            
            .semester-table tr:nth-child(even) {
                background: #f8f9fa;
            }
            
            .semester-table tr:hover {
                background: #e3f2fd;
            }
            
            .grade-A { color: #27ae60; font-weight: bold; }
            .grade-B { color: #f39c12; font-weight: bold; }
            .grade-C { color: #e67e22; font-weight: bold; }
            .grade-D { color: #e74c3c; font-weight: bold; }
            
            .summary-section {
                background: #2c3e50;
                color: white;
                padding: 20px;
                border-radius: 10px;
                margin-bottom: 25px;
            }
            
            .summary-title {
                font-size: 18px;
                margin-bottom: 15px;
                text-align: center;
                font-weight: bold;
            }
            
            .summary-grid {
                display: grid;
                grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
                gap: 15px;
            }
            
            .summary-item {
                background: rgba(255,255,255,0.1);
                padding: 15px;
                border-radius: 8px;
                text-align: center;
            }
            
            .summary-value {
                font-size: 24px;
                font-weight: bold;
                color: #3498db;
            }
            
            .summary-label {
                font-size: 12px;
                margin-top: 5px;
                opacity: 0.8;
            }
            
            .actions {
                text-align: center;
                margin: 30px 0;
            }
            
            .print-btn {
                background: linear-gradient(45deg, #e74c3c, #c0392b);
                color: white;
                border: none;
                padding: 15px 30px;
                border-radius: 25px;
                cursor: pointer;
                font-size: 16px;
                font-weight: bold;
                transition: all 0.3s ease;
                margin: 0 10px;
            }
            
            .print-btn:hover {
                transform: translateY(-2px);
                box-shadow: 0 5px 15px rgba(231, 76, 60, 0.3);
            }
            
            .footer {
                text-align: center;
                border-top: 2px solid #ecf0f1;
                padding-top: 20px;
                margin-top: 30px;
                color: #7f8c8d;
                font-size: 14px;
            }
            
            .signature-section {
                display: flex;
                justify-content: space-between;
                margin-top: 40px;
                padding-top: 20px;
            }
            
            .signature {
                text-align: center;
                width: 200px;
            }
            
            .signature-line {
                border-top: 2px solid #2c3e50;
                margin-bottom: 5px;
            }
            
            .signature-label {
                font-size: 12px;
                color: #7f8c8d;
                text-transform: uppercase;
            }
            
            /* Print Styles */
            @media print {
                body {
                    background: white;
                }
                
                .container {
                    box-shadow: none;
                    max-width: none;
                }
                
                .actions {
                    display: none;
                }
                
                .print-btn {
                    display: none;
                }
                
                * {
                    -webkit-print-color-adjust: exact;
                    print-color-adjust: exact;
                }
            }
        </style>
    `);

    // Generate the main content
    document.write(`
        <div class="container">
            <div class="header">
                <div class="university-logo">IIEST</div>
                <div class="university-name">Indian Institute of Engineering Science and Technology</div>
                <div class="department">Computer Science & Technology Department</div>
                <div class="report-title">Academic Performance Report</div>
            </div>
            
            <div class="student-info">
                <div class="info-row">
                    <span class="info-label">Student Name:</span>
                    <span class="info-value">Rahul Kumar Singh</span>
                </div>
                <div class="info-row">
                    <span class="info-label">Roll Number:</span>
                    <span class="info-value">CST/21/001</span>
                </div>
                <div class="info-row">
                    <span class="info-label">Registration No:</span>
                    <span class="info-value">21CST001</span>
                </div>
                <div class="info-row">
                    <span class="info-label">Academic Year:</span>
                    <span class="info-value">2023-2024</span>
                </div>
                <div class="info-row">
                    <span class="info-label">Current Semester:</span>
                    <span class="info-value">6th Semester</span>
                </div>
                <div class="info-row">
                    <span class="info-label">Report Generated:</span>
                    <span class="info-value">${new Date().toLocaleDateString()}</span>
                </div>
            </div>
            
            <h3 style="color: #2c3e50; margin-bottom: 15px; border-bottom: 2px solid #3498db; padding-bottom: 5px;">📚 Current Semester Subjects</h3>
            <table class="semester-table">
                <thead>
                    <tr>
                        <th>Subject Code</th>
                        <th>Subject Name</th>
                        <th>Credits</th>
                        <th>Grade</th>
                        <th>Grade Points</th>
                    </tr>
                </thead>
                <tbody>
    `);

    // Generate semester subjects data
    const subjects = [
        { code: 'CST601', name: 'Software Engineering', credits: 4, grade: 'A', points: 9 },
        { code: 'CST602', name: 'Computer Networks', credits: 4, grade: 'A', points: 9 },
        { code: 'CST603', name: 'Database Management Systems', credits: 4, grade: 'B+', points: 8 },
        { code: 'CST604', name: 'Operating Systems', credits: 4, grade: 'A', points: 9 },
        { code: 'CST605', name: 'Web Technologies', credits: 3, grade: 'A', points: 9 },
        { code: 'CST606', name: 'Machine Learning', credits: 3, grade: 'B+', points: 8 },
        { code: 'CST607L', name: 'Software Engineering Lab', credits: 2, grade: 'A', points: 9 },
        { code: 'CST608L', name: 'Database Lab', credits: 2, grade: 'A', points: 9 }
    ];

    subjects.forEach(subject => {
        let gradeClass = '';
        if (subject.grade.includes('A')) gradeClass = 'grade-A';
        else if (subject.grade.includes('B')) gradeClass = 'grade-B';
        else if (subject.grade.includes('C')) gradeClass = 'grade-C';
        else gradeClass = 'grade-D';

        document.write(`
            <tr>
                <td>${subject.code}</td>
                <td>${subject.name}</td>
                <td>${subject.credits}</td>
                <td class="${gradeClass}">${subject.grade}</td>
                <td>${subject.points}</td>
            </tr>
        `);
    });

    document.write(`
                </tbody>
            </table>
            
            <div class="summary-section">
                <div class="summary-title">📊 Academic Summary</div>
                <div class="summary-grid">
                    <div class="summary-item">
                        <div class="summary-value">8.65</div>
                        <div class="summary-label">Current SGPA</div>
                    </div>
                    <div class="summary-item">
                        <div class="summary-value">8.42</div>
                        <div class="summary-label">Overall CGPA</div>
                    </div>
                    <div class="summary-item">
                        <div class="summary-value">26</div>
                        <div class="summary-label">Total Credits</div>
                    </div>
                    <div class="summary-item">
                        <div class="summary-value">142</div>
                        <div class="summary-label">Credits Completed</div>
                    </div>
                </div>
            </div>
            
            <h3 style="color: #2c3e50; margin-bottom: 15px; border-bottom: 2px solid #e74c3c; padding-bottom: 5px;">🎯 Previous Semester Performance</h3>
            <table class="semester-table">
                <thead>
                    <tr>
                        <th>Semester</th>
                        <th>SGPA</th>
                        <th>Credits</th>
                        <th>Status</th>
                    </tr>
                </thead>
                <tbody>
                    <tr><td>Semester 1</td><td class="grade-A">8.2</td><td>22</td><td>✅ Passed</td></tr>
                    <tr><td>Semester 2</td><td class="grade-A">8.5</td><td>24</td><td>✅ Passed</td></tr>
                    <tr><td>Semester 3</td><td class="grade-A">8.1</td><td>26</td><td>✅ Passed</td></tr>
                    <tr><td>Semester 4</td><td class="grade-A">8.7</td><td>24</td><td>✅ Passed</td></tr>
                    <tr><td>Semester 5</td><td class="grade-A">8.3</td><td>20</td><td>✅ Passed</td></tr>
                </tbody>
            </table>
            
            <div class="actions">
                <button class="print-btn" onclick="window.print()">🖨️ Print Report</button>
                <button class="print-btn" onclick="downloadPDF()" style="background: linear-gradient(45deg, #27ae60, #229954);">📄 Download PDF</button>
            </div>
            
            <div class="signature-section">
                <div class="signature">
                    <div class="signature-line"></div>
                    <div class="signature-label">Student Signature</div>
                </div>
                <div class="signature">
                    <div class="signature-line"></div>
                    <div class="signature-label">Academic Officer</div>
                </div>
                <div class="signature">
                    <div class="signature-line"></div>
                    <div class="signature-label">Head of Department</div>
                </div>
            </div>
            
            <div class="footer">
                <p>This is a computer-generated report. No signature is required.</p>
                <p>For any queries, contact: academics@iiests.ac.in | Phone: +91-33-26684561</p>
                <p><strong>Generated on:</strong> ${new Date().toLocaleString()}</p>
            </div>
        </div>
    `);

    // Add JavaScript functions for interactivity
    document.write(`
        <script>
            function downloadPDF() {
                alert('PDF download functionality would be implemented here.\\nThis is a demonstration of the feature.');
                // In a real implementation, you would use libraries like jsPDF or html2pdf
            }
            
            // Auto-focus print when Ctrl+P is pressed
            document.addEventListener('keydown', function(e) {
                if (e.ctrlKey && e.key === 'p') {
                    e.preventDefault();
                    window.print();
                }
            });
            
            // Add some dynamic content
            console.log('Student Academic Report generated using document.write() method');
            console.log('Report Date: ' + new Date().toLocaleString());
        </script>
    `);
}

// Additional utility functions
function getCurrentDateTime() {
    return new Date().toLocaleString();
}

function calculateGPA(subjects) {
    let totalPoints = 0;
    let totalCredits = 0;
    
    subjects.forEach(subject => {
        totalPoints += subject.points * subject.credits;
        totalCredits += subject.credits;
    });
    
    return (totalPoints / totalCredits).toFixed(2);
}