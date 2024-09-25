#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>  // For mathematical operations
#include <ctype.h> // For character checking functions

// Define constants for string lengths
#define MAX_DESC_LEN 256
#define MAX_DATE_LEN 20

// Enum for menu choices to improve readability in the menu system
typedef enum
{
    ADD_ITEM = 1,
    LIST_ITEMS,
    MARK_COMPLETED,
    REMOVE_ITEM,
    SAVE_EXIT,
    FACTORIAL_CALCULATION
} MenuChoice;

// Struct for a to-do item, containing a description, due date, and completion status
typedef struct ToDoItem
{
    char description[MAX_DESC_LEN]; // Description of the to-do item
    char dueDate[MAX_DATE_LEN];     // Due date of the to-do item
    int isCompleted;                // Status: 0 = not completed, 1 = completed
} ToDoItem;

// Struct for the to-do list, managing an array of items dynamically
typedef struct ToDoList
{
    ToDoItem *items; // Pointer to dynamically allocated array of ToDoItems
    int size;        // Current number of items in the list
    int capacity;    // Current capacity of the dynamically allocated array
} ToDoList;

// Function to initialize the to-do list with a given capacity
void initToDoList(ToDoList *list, int capacity)
{
    list->items = (ToDoItem *)malloc(sizeof(ToDoItem) * capacity); // Allocate memory for 'capacity' items
    list->size = 0;                                                // Initially, the list has no items
    list->capacity = capacity;                                     // Set the initial capacity of the list
}

// Function to resize the to-do list when capacity is reached
void resizeToDoList(ToDoList *list)
{
    list->capacity *= 2;                                                               // Double the capacity
    list->items = (ToDoItem *)realloc(list->items, sizeof(ToDoItem) * list->capacity); // Reallocate memory for new capacity
}

// Function to add an item to the list with description and due date
void addItem(ToDoList *list, const char *desc, const char *dueDate)
{
    if (list->size == list->capacity) // If list is full, resize it
    {
        resizeToDoList(list);
    }
    // Copy the description and due date to the current item
    strcpy(list->items[list->size].description, desc);
    strcpy(list->items[list->size].dueDate, dueDate);
    list->items[list->size].isCompleted = 0; // Mark as not completed by default
    list->size++;                            // Increase the number of items in the list
}

// Function to list all items in the to-do list
void listItems(const ToDoList *list)
{
    for (int i = 0; i < list->size; ++i)
    {
        // Print each item with its status (completed or pending)
        printf("%d. %s (Due: %s) [%s]\n", i + 1, list->items[i].description, list->items[i].dueDate,
               list->items[i].isCompleted ? "Completed" : "Pending");
    }
}

// Function to mark an item as completed by its index
void markAsCompleted(ToDoList *list, int index)
{
    if (index >= 0 && index < list->size) // Ensure the index is valid
    {
        list->items[index].isCompleted = 1; // Set the completion status to true
    }
}

// Function to remove an item from the list by its index
void removeItem(ToDoList *list, int index)
{
    if (index >= 0 && index < list->size) // Ensure the index is valid
    {
        // Shift all items after the removed one to the left
        for (int i = index; i < list->size - 1; ++i)
        {
            list->items[i] = list->items[i + 1];
        }
        list->size--; // Reduce the size of the list
    }
}

// Function to save the list to a file
void saveToFile(const ToDoList *list, const char *filename)
{
    FILE *file = fopen(filename, "w"); // Open the file for writing
    if (file == NULL)
    {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    // Write each item to the file in CSV format (description, due date, completion status)
    for (int i = 0; i < list->size; ++i)
    {
        fprintf(file, "%s,%s,%d\n", list->items[i].description, list->items[i].dueDate, list->items[i].isCompleted);
    }

    fclose(file); // Close the file
}

// Function to load the list from a file
void loadFromFile(ToDoList *list, const char *filename)
{
    FILE *file = fopen(filename, "r"); // Open the file for reading
    if (file == NULL)
    {
        printf("No previous list found. Starting fresh.\n");
        return;
    }

    // Buffer to read lines from the file
    char buffer[MAX_DESC_LEN + MAX_DATE_LEN + 10];
    while (fgets(buffer, sizeof(buffer), file)) // Read each line
    {
        char desc[MAX_DESC_LEN], dueDate[MAX_DATE_LEN];
        int isCompleted;

        // Parse each line into description, due date, and completion status
        sscanf(buffer, "%[^,],%[^,],%d", desc, dueDate, &isCompleted);

        // Add the item to the list
        addItem(list, desc, dueDate);
        list->items[list->size - 1].isCompleted = isCompleted; // Set the completion status
    }

    fclose(file); // Close the file
}

// Function to calculate factorial using recursion
unsigned long long factorial(int n)
{
    if (n == 0 || n == 1) // Base case: factorial of 0 or 1 is 1
        return 1;
    return n * factorial(n - 1); // Recursive case
}

// Function to check if a string contains only digits (used for validating user input)
int isNumeric(const char *str)
{
    while (*str)
    {
        if (!isdigit(*str)) // Check if each character is a digit
        {
            return 0;
        }
        str++;
    }
    return 1;
}

// Function to free up the dynamically allocated memory for the to-do list
void freeToDoList(ToDoList *list)
{
    free(list->items); // Free the allocated memory
}

// Main program
int main()
{
    ToDoList todoList;
    initToDoList(&todoList, 5);          // Initialize the list with a capacity of 5 items
    loadFromFile(&todoList, "todo.txt"); // Load existing items from the file

    int choice;
    do
    {
        // Display the menu
        printf("1. Add Item\n");
        printf("2. List Items\n");
        printf("3. Mark Item as Completed\n");
        printf("4. Remove Item\n");
        printf("5. Save and Exit\n");
        printf("6. Factorial Calculation (Recursion)\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character after input

        switch (choice)
        {
        case ADD_ITEM:
        {
            char desc[MAX_DESC_LEN], dueDate[MAX_DATE_LEN];
            printf("Enter description: ");
            fgets(desc, sizeof(desc), stdin); // Get the item description
            desc[strcspn(desc, "\n")] = 0;    // Remove trailing newline
            printf("Enter due date: ");
            fgets(dueDate, sizeof(dueDate), stdin); // Get the due date
            dueDate[strcspn(dueDate, "\n")] = 0;    // Remove trailing newline
            addItem(&todoList, desc, dueDate);      // Add the item to the list
            break;
        }
        case LIST_ITEMS:
            listItems(&todoList); // List all items
            break;
        case MARK_COMPLETED:
        {
            int index;
            printf("Enter item number to mark as completed: ");
            scanf("%d", &index);
            markAsCompleted(&todoList, index - 1); // Mark the specified item as completed
            break;
        }
        case REMOVE_ITEM:
        {
            int index;
            printf("Enter item number to remove: ");
            scanf("%d", &index);
            removeItem(&todoList, index - 1); // Remove the specified item
            break;
        }
        case SAVE_EXIT:
            saveToFile(&todoList, "todo.txt"); // Save the list to a file
            printf("Changes saved. Exiting.\n");
            break;
        case FACTORIAL_CALCULATION:
        {
            char input[10];
            printf("Enter a positive integer to calculate its factorial: ");
            fgets(input, sizeof(input), stdin); // Get input from user
            input[strcspn(input, "\n")] = 0;    // Remove trailing newline

            if (isNumeric(input)) // Check if the input is a valid number
            {
                int num = atoi(input);                                     // Convert string to integer
                printf("Factorial of %d is: %llu\n", num, factorial(num)); // Calculate factorial
            }
            else
            {
                printf("Invalid input! Please enter a valid positive integer.\n");
            }
            break;
        }
        default:
            if (choice != SAVE_EXIT)
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != SAVE_EXIT); // Continue until the user chooses to save and exit

    freeToDoList(&todoList); // Free allocated memory
    return 0;
}
