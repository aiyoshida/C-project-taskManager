## Overview
The Task Manager project is a C program developed as part of a course assignment for "The Basics of Programming" at Budapest University of Technology and Economics (BME). This program allows users to manage tasks using a command-line interface, supporting features such as task creation, viewing unfinished tasks, categorizing tasks, and managing task dependencies.

## Student Information
- **Name**: Ai Yoshida
- **Neptun Code**: FPYYT9
- **Class**: The Basics of Programming
- **Professor**: Harvoth Gabor

## Features
- Create new tasks with details including name, description, category, start and end dates, priority, and dependencies.
- View a list of unfinished tasks, sorted chronologically.
- Categorize tasks and view tasks by category.
- Manage and view tasks based on their dependencies.

## Technologies Used
- **C Standard Library**: Utilizes `stdio.h`, `stdlib.h`, and `string.h` for basic functionalities, memory allocation, and string operations.
- **Data Structures**: Uses linked lists to manage tasks.

## Data Structures
The program uses the following data structure to represent tasks:
```c
typedef struct tasks {
    char task_name[20];
    char task_description[200];
    char categories[20];
    int s_year, s_month, s_day; // Start date
    int e_year, e_month, e_day; // End date
    int priority; // Priority (1 to 10)
    char dep[20]; // Dependencies
    struct tasks *next; // Pointer to the next task
} tasks;
