// Name: Mpho Khoza
// Student Number: 51468956

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// Constants
const int MAX_TASKS = 50;
const string FILE_NAME = "tasks.txt";

// Struct
struct Task {
    string description;
    string dueDate;      // "YYYY-MM-DD"
    int priority;        // 1 = High, 2 = Medium, 3 = Low
    bool completed;      // true = done
};

// Function Prototypes
void loadTasks(Task* tasks, int& count);
void saveTasks(Task* tasks, int count);
void addTask(Task* tasks, int& count);
void displayTasks(Task* tasks, int count);
void markTaskCompleted(Task* tasks, int count);
void deleteTask(Task* tasks, int& count);
void sortTasks(Task* tasks, int count);
void searchTasks(Task* tasks, int count);
void summary(Task* tasks, int count);
string priorityToText(int p);
string statusToText(bool s);
void pause();

// Main
int main() {
    Task tasks[MAX_TASKS];
    int count = 0;
    loadTasks(tasks, count);

    int choice;
    do {
        cout << "\n===== MO'S TO-DO LIST =====\n";
        cout << "1. Add Task\n";
        cout << "2. View All Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Delete a Task\n";
        cout << "5. Sort Tasks (by Priority)\n";
        cout << "6. Search Tasks (by Keyword)\n";
        cout << "7. Show Summary\n";
        cout << "8. Exit\n";
        cout << "==============================\n";
        cout << "Enter choice: ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice, try again: ";
            cin >> choice;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

        switch (choice) {
            case 1: addTask(tasks, count); break;
            case 2: displayTasks(tasks, count); pause(); break;
            case 3: markTaskCompleted(tasks, count); break;
            case 4: deleteTask(tasks, count); break;
            case 5: sortTasks(tasks, count); break;
            case 6: searchTasks(tasks, count); pause(); break;
            case 7: summary(tasks, count); pause(); break;
            case 8: saveTasks(tasks, count);
                    cout << "\nTasks saved successfully. Goodbye!\n";
                    break;
        }
    } while (choice != 8);

    return 0;
}

// Functions

void loadTasks(Task* tasks, int& count) {
    ifstream inFile(FILE_NAME);
    if (!inFile) {
        count = 0;
        return;
    }

    count = 0;
    while (inFile && count < MAX_TASKS) {
        Task t;
        string status;
        getline(inFile, t.description);
        if (t.description.empty()) break;
        getline(inFile, t.dueDate);
        inFile >> t.priority;
        inFile >> status;
        inFile.ignore();
        t.completed = (status == "1");
        *(tasks + count) = t;
        count++;
    }
    inFile.close();
}

void saveTasks(Task* tasks, int count) {
    ofstream outFile(FILE_NAME);
    for (int i = 0; i < count; i++) {
        outFile << (tasks + i)->description << "\n"
                << (tasks + i)->dueDate << "\n"
                << (tasks + i)->priority << "\n"
                << ((tasks + i)->completed ? 1 : 0) << "\n";
    }
    outFile.close();
}

void addTask(Task* tasks, int& count) {
    if (count >= MAX_TASKS) {
        cout << "Task limit reached!\n";
        return;
    }

    Task t;
    cout << "Enter task description: ";
    getline(cin, t.description);
    cout << "Enter due date (YYYY-MM-DD): ";
    getline(cin, t.dueDate);

    do {
        cout << "Enter priority (1=High, 2=Medium, 3=Low): ";
        cin >> t.priority;
    } while (t.priority < 1 || t.priority > 3);

    t.completed = false;
    *(tasks + count) = t;
    count++;
    saveTasks(tasks, count);
    cout << "Task added successfully!\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayTasks(Task* tasks, int count) {
    if (count == 0) {
        cout << "No tasks available.\n";
        return;
    }

    cout << left << setw(5) << "#" << setw(25) << "Description"
         << setw(14) << "Due Date" << setw(10) << "Priority" << "Status" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < count; i++) {
        Task t = *(tasks + i);
        cout << left << setw(5) << (i + 1)
             << setw(25) << t.description.substr(0, 23)
             << setw(14) << t.dueDate
             << setw(10) << priorityToText(t.priority)
             << statusToText(t.completed)
             << endl;
    }
}

void markTaskCompleted(Task* tasks, int count) {
    if (count == 0) {
        cout << "No tasks to mark.\n";
        return;
    }

    displayTasks(tasks, count);
    int index;
    cout << "\nEnter task number to mark as completed: ";
    cin >> index;

    if (index < 1 || index > count) {
        cout << "Invalid task number.\n";
        return;
    }

    (tasks + index - 1)->completed = true;
    cout << "Task marked as completed!\n";
    saveTasks(tasks, count);
}

void deleteTask(Task* tasks, int& count) {
    if (count == 0) {
        cout << "No tasks to delete.\n";
        return;
    }

    displayTasks(tasks, count);
    int index;
    cout << "\nEnter task number to delete: ";
    cin >> index;

    if (index < 1 || index > count) {
        cout << "Invalid task number.\n";
        return;
    }

    for (int i = index - 1; i < count - 1; i++) {
        *(tasks + i) = *(tasks + i + 1);
    }
    count--;
    cout << "Task deleted.\n";
    saveTasks(tasks, count);
}

void sortTasks(Task* tasks, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if ((tasks + j)->priority < (tasks + i)->priority) {
                Task temp = *(tasks + i);
                *(tasks + i) = *(tasks + j);
                *(tasks + j) = temp;
            }
        }
    }
    cout << "Tasks sorted by priority.\n";
    saveTasks(tasks, count);
}

void searchTasks(Task* tasks, int count) {
    string keyword;
    cout << "Enter keyword to search: ";
    getline(cin, keyword);

    bool found = false;
    cout << "\nSearch results for \"" << keyword << "\":\n";
    cout << string(60, '-') << endl;

    for (int i = 0; i < count; i++) {
        if ((tasks + i)->description.find(keyword) != string::npos) {
            cout << (i + 1) << ". " << (tasks + i)->description
                 << " (" << statusToText((tasks + i)->completed) << ")\n";
            found = true;
        }
    }
    if (!found)
        cout << "No tasks found matching \"" << keyword << "\".\n";
}

void summary(Task* tasks, int count) {
    int done = 0;
    for (int i = 0; i < count; i++)
        if ((tasks + i)->completed)
            done++;

    cout << "\nTotal Tasks: " << count
         << "\nCompleted: " << done
         << "\nPending: " << (count - done);

    double percent = (count == 0) ? 0 : (done * 100.0 / count);
    cout << "\nCompletion: " << fixed << setprecision(1) << percent << "%\n";
}

string priorityToText(int p) {
    if (p == 1) return "High";
    if (p == 2) return "Medium";
    return "Low";
}

string statusToText(bool s) {
    return s ? "Done" : "Pending";
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
