# Task Scheduler with Priority Queue

## Overview
This project implements a **Task Scheduler** using a **Priority Queue** implemented as a **Linked List**. It reads tasks from a file, processes them based on priority, and implements an **adaptive scheduling mechanism**.

## Features
- **Priority Queue**: Tasks with higher priority (lower numerical value) are executed first.
- **Adaptive Scheduling**: If a task is scheduled multiple times, its allocated time slice increases.
- **Task Preemption**: If a task is not completed within its allocated time slice, it is reinserted into the queue with a lower priority.
- **Custom String Functions**: Implements custom versions of `find`, `substr`, and `stoi` for parsing input.
- **File Input Support**: Reads tasks from `tasks.txt`.

## How It Works
1. Reads tasks from a file (`tasks.txt`) with the format:
   ```
   TaskID,TaskType,ComputationTime,Priority
   ```
2. Inserts tasks into the **Priority Queue** based on priority.
3. Executes tasks in order of priority:
   - Assigns an initial time slice of **3 units**.
   - If a task is rescheduled **4 or more times**, its time slice increases.
   - If a task is unfinished, it is **requeued with a lower priority**.
4. Prints execution details for each task.

## File Format (`tasks.txt`)
Each task entry should be on a new line in the format:
```
1,Computation,10,2
2,IO,5,1
3,Processing,8,3
```
- **Task ID**: Unique identifier for the task.
- **Task Type**: Type of task (Computation, IO, etc.).
- **Computation Time**: Total time required to complete the task.
- **Priority**: Lower values indicate higher priority.

## How to Run
### **On Ubuntu or Any Linux System**
1. Open a terminal and navigate to the project folder:
   ```sh
   cd /path/to/project
   ```
2. Compile the program:
   ```sh
   g++ task_scheduler.cpp -o task_scheduler
   ```
3. Run the executable:
   ```sh
   ./task_scheduler
   ```

## Example Output
```
Executing Task ID: 2 (IO)
Scheduled 1 times before.
Remaining Computation Time: 5 units
Allocated Time Slice: 3 units
Task 2 not completed. Requeuing with new priority 2
---------------------
Executing Task ID: 2 (IO)
Scheduled 2 times before.
Remaining Computation Time: 2 units
Allocated Time Slice: 3 units
Task 2 completed.
---------------------
```

## Memory Management
- Uses a **linked list** for task storage.
- Ensures **dynamic memory allocation** is properly freed upon completion.
- **Destructor (`~PriorityQueue`) cleans up memory** when the queue is no longer needed.

## Dependencies
- **C++ Standard Library** (`<iostream>`, `<fstream>`) – No external libraries required.

## Future Improvements
- Implement **multi-threading** for parallel execution.
- Improve **task scheduling algorithm** for efficiency.
- Add **task categories** with different priority adjustments.

## Author
Developed by **Muhammad Saqib Atif**.

