# 🧠 Data Structures Tutor Chatbot (C++)

## 📌 Overview
The **Data Structures Tutor Chatbot** is an interactive command-line learning assistant developed in C++. It helps students and beginners explore key data structure concepts such as AVL Trees, Binary Search Trees, Linked Lists, and more through user-friendly interactions.

By typing questions or commands, users can:
- Navigate topics and subtopics from file-based content.
- View dynamic AVL Tree visualizations.
- Learn interactively via context-based keyword recognition.

---

## ⚙️ Implemented Concepts

This chatbot integrates the following fundamental programming and data structure concepts:

1. **AVL Tree** – Self-balancing BST with automatic rotations (LL, RR, LR, RL).
2. **Binary Search Tree (BST)** – Tree-based data organization with search efficiency.
3. **Preorder Traversal** – Used for structured output and logical processing.
4. **File Handling** – Loads and manages educational content from `.txt` files.
5. **Keyword Extraction** – Processes and maps queries to relevant content.
6. **Directory-Based Topic Management** – Organizes topics in a folder hierarchy.
7. **Input Preprocessing** – Lowercasing, tokenizing, and punctuation removal.
8. **Scoring Mechanism** – Scores topics for the best match based on relevance.
9. **Linked List** – Supports internal structure handling (optional use).
10. **Dynamic Memory Allocation** – Enables runtime memory for tree nodes.
11. **Recursive Functions** – Powers AVL insertion, balancing, and traversal.
12. **String Manipulation** – Handles formatting, tokenizing, and matching.
13. **Maps/Dictionaries (Conceptual)** – Maps topics to subtopics efficiently.
14. **User Interaction and Query Handling** – Converts questions into answers.
15. **Modular Code Structure** – Clean function separation for scalability.
16. **Sorting** – Orders topics/subtopics when presenting content.

---

## 💡 Key Functionalities

### 📁 1. Topic Management
- Loads topics dynamically from the `/topics/` folder.
- Automatically processes topic names for uniformity.
- Recognizes relevant topics using keyword scoring.

### 📄 2. Subtopic Matching
- Each topic contains multiple subtopics stored in text files.
- Matches user input to subtopics using keyword overlap and context.
- Parses files and returns targeted explanations.

### 🌳 3. Interactive AVL Tree Demo
- Users can input values to create and balance AVL trees.
- Rotations are applied automatically to maintain balance.
- The tree structure is visualized in a simple ASCII format.

### 🧠 4. Smart Keyword Context Mapping
- Context-aware scoring maps user queries to topics/subtopics.
- Adjusts dynamically based on synonyms or related terms.

### 🧵 5. Smooth User Conversation Flow
- Uses a queue system for organizing and displaying responses.
- Error-handling ensures meaningful fallback messages.
  
## 👥 Contributors

- **Muhammad Abdullah Younas**
- **Ayema Amir**  

## 🛡 License

This work is licensed for academic demonstration only.  
🚫 **Reproduction or reuse without permission is prohibited.**
