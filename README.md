# 🎓 Computer Science Coursework Portfolio

<div align="center">
  <img src="https://img.shields.io/badge/academic-portfolio-blue.svg?style=for-the-badge&logo=github" alt="Academic Portfolio" />
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++" />
  <img src="https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white" alt="Python" />
  <img src="https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=black" alt="C" />
  <img src="https://img.shields.io/badge/MySQL-4479A1?style=for-the-badge&logo=mysql&logoColor=white" alt="MySQL" />
  <img src="https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black" alt="JavaScript" />
</div>

<br />

A comprehensive repository containing programming assignments, projects, and laboratory coursework spanning a wide array of core Computer Science subjects. This collection demonstrates practical implementations of key theoretical concepts, algorithmic problem-solving, and software development methodologies.

## 📁 Repository Structure & Modules

### 🧩 [Algorithms](./Algorithms/)
Advanced algorithm implementations and empirical performance analysis:
- **Sorting & Searching:** Implementations and empirical comparisons of sorting algorithms.
- **Divide & Conquer:** Min/max finding, tournament methods.
- **Graph Algorithms:** Minimum Spanning Trees (Kruskal's & Prim's algorithms).
- **String Algorithms:** Pattern matching techniques.
- **Data Analysis:** Practical application of algorithms on datasets (e.g., Online News Popularity analysis using pandas).

### 🌐 [Computer Networks](./Computer%20Networks/)
Network communication and protocol implementations:
- **Socket Programming:** Client-server architectures using standard C sockets (TCP/UDP protocols).

### 📚 [Data Structures](./Data%20Structures/)
Fundamental and advanced data structure implementations (primarily in C):
- **Core Structures:** Linked lists, stacks, queues, and tree implementations.
- **Advanced Applications:** Memory pool management, large number arithmetic, polynomial operations, and the Josephus problem.
- **Expression Evaluation:** Postfix/Prefix expression parsers and evaluators.

### 🗄️ [Database Management Systems (DBMS)](./DBMS/)
Database design, normalization, and advanced SQL querying:
- **Schema Design:** Relational database schemas for domains like Colleges and Logistics environments.
- **SQL Operations:** Complex queries, aggregations, triggers, and comprehensive views representing business logic.

### 🕸️ [Graph Algorithms](./Graph%20Algorithms/)
In-depth exploration of graph theory algorithms:
- **Traversal:** Breadth-First Search (BFS) and Depth-First Search (DFS).
- **Component Analysis:** Strongly connected components (Kosaraju's & Tarjan's algorithms), bipartite checking, graph isomorphism, and splicing techniques.

### 💻 [Operating Systems](./Operating%20Systems/)
System programming demonstrating OS core mechanics:
- **Process Management:** Process creation (ork, exec), process synchronization, and inter-process communication.
- **Concurrency:** Semaphores handling multi-threading and classic synchronization problems.
- **Memory & Filesystems:** Shared memory applications and basic filesystem abstractions.

### 🏛️ [Programming Paradigms](./paradigms/)
Exploration of multiple programming languages and their specific paradigms:
- **Object-Oriented Programming (OOP):** Custom memory management, generic programming (templates), multiple and virtual inheritance.
- **Performance Profiling:** Comparative analysis of paradigm-specific approaches.

### 🎨 [Web Technology](./Web%20Technology/)
Front-end and full-stack web development coursework:
- **Fundamentals:** HTML5, modern CSS3 styling, and foundational JavaScript (index.js).
- **Interactive UI:** Step-by-step assignments building up responsive and interactive user interfaces.

---

## 🛠️ Technologies Used

| Category | Tools & Technologies |
|---|---|
| **Languages** | C, C++, Python, SQL, JavaScript, HTML, CSS |
| **Libraries/Frameworks** | STL, Pandas, Matplotlib, Seaborn |
| **Environments** | Linux/Unix Utilities, GCC, Bash, Jupyter Notebooks |
| **Concepts** | Memory Management, OOP, Metaprogramming, Graph Theory, Relational Algebra, System Calls |

## 🚀 Setup & Execution

Since this is a multi-language repository, execution steps depend heavily on the specific module being tested.

### C / C++ Modules
Requires standard \gcc\ / \g++\ compilers:
\\\ash
g++ -o output [filename.cpp]
./output
\\\

### Python Modules
Ensure Python 3.8+ and pip are installed. A virtual environment is recommended for data-science specific assignments:
\\\ash
pip install pandas matplotlib jupyter
# To run python files:
python main.py
# To view notebooks:
jupyter notebook
\\\

### Java / Web / DB
- **DBMS:** Import the provided .sql dump files into a local MySQL/PostgreSQL runner.
- **Web Technologies:** Open the index.html file using any modern browser or via Live Server in VS Code.
- **Computer Networks:** Compile server and client files separately mapping specific ports on localhost.

## 📈 Learning Outcomes

- **Algorithmic Efficiency:** Understanding Big-O complexities through practical implementation.
- **System Internals:** Managing raw sockets, memory pools, and system processes.
- **Software Design:** Applying OOP principles, polymorphism, and modular architectures to scale solutions.
- **Data Management:** From memory manipulation via pointers, to persistent relational databases.
