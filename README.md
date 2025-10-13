# MO-TO-DO-CMPG-Creative-Project-
📖 Description

The To-Do List Manager is a lightweight, console-based productivity application built in C++.
It allows users to manage their daily tasks by adding, updating, deleting, sorting, and searching through them — all from the terminal.
The program uses file storage to automatically save your progress, ensuring that your to-do list is available each time you reopen the app.

This project was created as part of the CMPG121 Creative Programming Project, showcasing the use of structs, arrays, pointers, functions, sorting, searching, and file I/O in a practical, real-world scenario.

🧠 Project Overview

The To-Do List Manager helps users:

Keep track of personal or academic tasks

Prioritize tasks by importance

Mark completed tasks and monitor progress

Automatically save tasks to a file for persistence

View summaries and completion percentages

🧩 Features
Feature	Description
➕ Add Task	Add new tasks with description, due date, and priority level
📜 View Tasks	Display all tasks in a formatted table with status indicators
✅ Mark Completed	Mark any task as completed
❌ Delete Task	Remove tasks that are no longer needed
🔍 Search Tasks	Find tasks by keyword within their description
🔼 Sort Tasks	Sort tasks by priority (High → Low)
📊 Summary Report	Displays total, completed, pending, and completion percentage
💾 File Handling	Automatically loads and saves tasks from tasks.txt
⚙️ Concepts Demonstrated

This project showcases key C++ programming concepts:

Structs: Representing tasks with related fields

Arrays & Pointers: Managing multiple tasks dynamically

Functions: Clean modular design and reusability

Sorting & Searching: Implemented manually using loops and pointer arithmetic

File I/O: Persistent data storage using fstream

Input Validation: Preventing invalid menu choices or entries

Formatted Output: Using <iomanip> for a clear, readable console interface

🧱 File Structure
main.cpp          → main source code
tasks.txt         → saved task data file
README.md         → documentation file

💻 How to Run

Clone this repository

git clone https://github.com/yourusername/todo-list-manager-cpp.git
cd todo-list-manager-cpp


Compile the code

g++ main.cpp -o ToDoList


Run the program

./ToDoList


The program will automatically create and update tasks.txt as you add or remove tasks.
