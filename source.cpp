#include <iostream>
#include <fstream>

using namespace std;

// Node structure for Priority Queue
class Node {
public:
    int taskID;
    string taskType;
    int computationTime;
    int priority;
    int timesScheduled;
    Node* next;
    
    Node(int id, string type, int time, int prio)
        : taskID(id), taskType(type), computationTime(time), priority(prio), timesScheduled(0), next(nullptr) {}
};

// Priority Queue using Linked List
class PriorityQueue {
private:
    Node* head; // Points to the highest priority task (smallest priority value)

public:
    PriorityQueue() : head(nullptr) {}

    void push(int id, string type, int time, int prio) {
        Node* newNode = new Node(id, type, time, prio);
        if (!head || prio < head->priority) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next && temp->next->priority <= prio) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    Node* pop() {
        if (!head) return nullptr;
        Node* temp = head;
        head = head->next;
        return temp;
    }

    bool empty() const {
        return head == nullptr;
    }

    void print() {
        Node* temp = head;
        while (temp) {
            cout << "ID: " << temp->taskID << ", Type: " << temp->taskType
                 << ", Time: " << temp->computationTime << ", Priority: " << temp->priority << endl;
            temp = temp->next;
        }
    }

    ~PriorityQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Priority Queue instance
PriorityQueue taskQueue;

// Custom function to find the position of a delimiter
size_t custom_find(const string& str, char delimiter) {
    size_t i;
    for ( i = 0; i < str.size(); ++i) {
        if (str[i] == delimiter) {
            return i;
        }
    }
    return i;
}

// Custom function to extract substring
string custom_substr(const string& str, size_t start, size_t length) {
    string result;
    for (size_t i = start; i < start + length && i < str.size(); ++i) {
        result += str[i];
    }
    return result;
}

// Custom function to convert string to integer
int custom_to_int(const string& str) {
    int num = 0;
    for (char ch : str) {
        if (ch >= '0' && ch <= '9') {
            num = num * 10 + (ch - '0');
        }
    }
    return num;
}

// Function to Add Task from File
void addTasksFromFile(string filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    int id, time, prio;
    string type;
    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        pos = custom_find(line, ',');
        id = custom_to_int(custom_substr(line, 0, pos));
        line = custom_substr(line, pos + 1, line.size() - pos - 1);

        pos = custom_find(line, ',');
        type = custom_substr(line, 0, pos);
        line = custom_substr(line, pos + 1, line.size() - pos - 1);

        pos = custom_find(line, ',');
        time = custom_to_int(custom_substr(line, 0, pos));
        line = custom_substr(line, pos + 1, line.size() - pos - 1);

        prio = custom_to_int(line);

        taskQueue.push(id, type, time, prio);
    }
    file.close();
}

// Function to Execute Next Task
void executeNextTask() {
    if (taskQueue.empty()) {
        cout << "No tasks to execute." << endl;
        return;
    }

    Node* currentTask = taskQueue.pop();
    
    currentTask->timesScheduled++;
    int timeSlice = 3;
    
    // Adaptive Scheduling: Increase Time Slice
    if (currentTask->timesScheduled >= 4)
        timeSlice *= currentTask->timesScheduled - 2;
    
    cout << "Executing Task ID: " << currentTask->taskID << " (" << currentTask->taskType << ")" << endl;
    cout << "Scheduled " << currentTask->timesScheduled << " times before." << endl;
    cout << "Remaining Computation Time: " << currentTask->computationTime << " units" << endl;
    cout << "Allocated Time Slice: " << timeSlice << " units" << endl;
    
    // Reduce Computation Time
    currentTask->computationTime -= timeSlice;
    
    if (currentTask->computationTime > 0) {
        // Reduce Priority and Reinsert
        if (currentTask->priority < 6) currentTask->priority++;
        taskQueue.push(currentTask->taskID, currentTask->taskType, currentTask->computationTime, currentTask->priority);
        cout << "Task " << currentTask->taskID << " not completed. Requeuing with new priority " << currentTask->priority << "\n";
    } else {
        cout << "Task " << currentTask->taskID << " completed." << endl;
        delete currentTask; // Free memory
    }
}

// Function to Display All Tasks
void displayTasks() {
    taskQueue.print();
}

int main() {
    // Load tasks from file
    addTasksFromFile("tasks.txt");
    
    // Execute tasks until queue is empty
    while (!taskQueue.empty()) {
        executeNextTask();
        cout << "---------------------\n";
    }
    return 0;
}
