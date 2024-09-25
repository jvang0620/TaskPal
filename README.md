# Command-Line To-Do List Manager

## Overview

This is a simple command-line To-Do List Manager written in C. The application allows users to efficiently manage their tasks via a terminal interface. With support for adding, listing, completing, and removing tasks, it is lightweight and ideal for quick task tracking. It also saves tasks to a file to ensure they persist between program executions, making it useful even after closing and reopening the app.

### Features:

- **Add Tasks**: Users can add new tasks with a description and a due date.
- **List Tasks**: Displays all tasks along with their due dates and completion status.
- **Mark as Completed**: Users can mark tasks as completed.
- **Remove Tasks**: Users can delete tasks from the list.
- **Save to File**: The current to-do list can be saved to a text file for persistence.
- **Load from File**: The application can load a previously saved to-do list when it starts.

## How It Works

The application uses `structs` to represent tasks (to-do items) and a dynamically resizable array to store them. The list grows as new items are added. Tasks are saved to a file so they are retained even after the program is closed, ensuring persistence.

## Files:

- `todo.c`: The source code of the program.
- `todo.txt`: A file used to store to-do items between sessions (created automatically upon saving).

---

## Installation and Compilation

### Prerequisites

To run this program, you'll need:

- A C compiler (e.g., `gcc`).
- A terminal to execute the program.

### Steps:

1. **Download the Source Code**:

   - Clone the repository or download the `todo.c` file directly to your local machine.

2. **Compile the Program**:
   Open a terminal and navigate to the folder where the `todo.c` file is located. Run the following command to compile the program:

   ```bash
   gcc -o todo src/todo.c
   ```

   This will create an executable file named `todo`.

3. **Run the Program**:
   After compiling, you can run the program by typing:

   ```bash
   ./todo
   ```

## Usage

When the program starts, you will be prompted with a menu offering several options:

    1. Add Item
    2. List Items
    3. Mark Item as Completed
    4. Remove Item
    5. Save and Exit
    6. Factorial Calculation (Recursion)
    Enter your choice:

### 1. Add Item

- You will be prompted to enter a task description and a due date.
- Examples:

  ```bash
  Enter description: Buy groceries
  Enter due date: 2024-09-30
  ```

- This will add the task to the to-do list.

### 2. List Items

- Displays all current tasks in the list along with their due dates and completion statuses.
- Example output:

  ```bash
  1. Buy groceries (Due: 2024-09-30) [Pending]
  2. Finish project (Due: 2024-09-28) [Completed]
  ```

### 3. Mark Item as Completed

- You will be prompted to enter the task number to mark as completed.
- Example:

  ```bash
  Enter item number to mark as completed: 1
  ```

- This marks the corresponding task as completed.

### 4. Remove Item

- You will be prompted to enter the task number to remove from the list.
- Example:

  ```bash
  Enter item number to remove: 2
  ```

- This removes the corresponding task from the to-do list.

### 5. Save and Exit

- Saves the current to-do list to a file named todo.txt and exits the program.
- The list will be reloaded when you run the program again.

## Program Structure

The key parts of the program are:

- `ToDoItem` struct: Holds the task description, due date, and completion status.
- `ToDoList` struct: Holds a dynamic array of `ToDoItems`, managing the list's size and capacity.
- **Dynamic memory allocation**: The to-do list grows dynamically as tasks are added, ensuring the program can handle as many tasks as needed.
- File I/O: Tasks are saved to `todo.txt` and loaded back when the program restarts, providing persistence.

## Future Improvements

- Add task priorities (low, medium, high).
- Add sorting of tasks by due date or priority.
- Allow editing of existing tasks.
# TaskPal
