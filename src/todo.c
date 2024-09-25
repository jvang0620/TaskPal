#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>  // For mathematical operations
#include <ctype.h> // For character checking functions

// Define constants for string lengths
#define MAX_DESC_LEN 256
#define MAX_DATE_LEN 20

// Enum for menu choices
typedef enum
{
    ADD_ITEM = 1,
    LIST_ITEMS,
    MARK_COMPLETED,
    REMOVE_ITEM,
    SAVE_EXIT,
    FACTORIAL_CALCULATION
} MenuChoice;

// Struct for a to-do item
typedef struct ToDoItem
{
    char description[MAX_DESC_LEN];
    char dueDate[MAX_DATE_LEN];
    int isCompleted; // 0 = not completed, 1 = completed
} ToDoItem;

// Struct for the to-do list
typedef struct ToDoList
{
    ToDoItem *items;
    int size;
    int capacity;
} ToDoList;

// Function to initialize the to-do list
void initToDoList(ToDoList *list, int capacity)
{
    list->items = (ToDoItem *)malloc(sizeof(ToDoItem) * capacity);
    list->size = 0;
    list->capacity = capacity;
}

// Function to resize the to-do list when needed
void resizeToDoList(ToDoList *list)
{
    list->capacity *= 2;
    list->items = (ToDoItem *)realloc(list->items, sizeof(ToDoItem) * list->capacity);
}

// Function to add an item to the list
void addItem(ToDoList *list, const char *desc, const char *dueDate)
{
    if (list->size == list->capacity)
    {
        resizeToDoList(list);
    }
    strcpy(list->items[list->size].description, desc);
    strcpy(list->items[list->size].dueDate, dueDate);
    list->items[list->size].isCompleted = 0; // Not completed by default
    list->size++;
}

// Function to list all items
void listItems(const ToDoList *list)
{
    for (int i = 0; i < list->size; ++i)
    {
        printf("%d. %s (Due: %s) [%s]\n", i + 1, list->items[i].description, list->items[i].dueDate,
               list->items[i].isCompleted ? "Completed" : "Pending");
    }
}

// Function to mark an item as completed
void markAsCompleted(ToDoList *list, int index)
{
    if (index >= 0 && index < list->size)
    {
        list->items[index].isCompleted = 1;
    }
}

// Function to delete an item from the list
void removeItem(ToDoList *list, int index)
{
    if (index >= 0 && index < list->size)
    {
        for (int i = index; i < list->size - 1; ++i)
        {
            list->items[i] = list->items[i + 1]; // Shift items to fill the gap
        }
        list->size--;
    }
}

// Function to save the list to a file
void saveToFile(const ToDoList *list, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    for (int i = 0; i < list->size; ++i)
    {
        fprintf(file, "%s,%s,%d\n", list->items[i].description, list->items[i].dueDate, list->items[i].isCompleted);
    }

    fclose(file);
}

// Function to load the list from a file
void loadFromFile(ToDoList *list, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("No previous list found. Starting fresh.\n");
        return;
    }

    char buffer[MAX_DESC_LEN + MAX_DATE_LEN + 10]; // Buffer to read lines from file
    while (fgets(buffer, sizeof(buffer), file))
    {
        char desc[MAX_DESC_LEN], dueDate[MAX_DATE_LEN];
        int isCompleted;
        sscanf(buffer, "%[^,],%[^,],%d", desc, dueDate, &isCompleted); // Parse each line

        addItem(list, desc, dueDate); // Add item to the list
        list->items[list->size - 1].isCompleted = isCompleted;
    }

    fclose(file);
}

// Function to calculate factorial using recursion
unsigned long long factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

// Function to check if a string contains only digits (helper function for user input)
int isNumeric(const char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
        {
            return 0;
        }
        str++;
    }
    return 1;
}

// Function to clean up memory
void freeToDoList(ToDoList *list)
{
    free(list->items);
}

// Main program
int main()
{
    ToDoList todoList;
    initToDoList(&todoList, 5); // Start with capacity for 5 items
    loadFromFile(&todoList, "todo.txt");

    int choice;
    do
    {
        printf("1. Add Item\n");
        printf("2. List Items\n");
        printf("3. Mark Item as Completed\n");
        printf("4. Remove Item\n");
        printf("5. Save and Exit\n");
        printf("6. Factorial Calculation (Recursion)\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume the newline character

        switch (choice)
        {
        case ADD_ITEM:
        {
            char desc[MAX_DESC_LEN], dueDate[MAX_DATE_LEN];
            printf("Enter description: ");
            fgets(desc, sizeof(desc), stdin);
            desc[strcspn(desc, "\n")] = 0; // Remove trailing newline
            printf("Enter due date: ");
            fgets(dueDate, sizeof(dueDate), stdin);
            dueDate[strcspn(dueDate, "\n")] = 0; // Remove trailing newline
            addItem(&todoList, desc, dueDate);
            break;
        }
        case LIST_ITEMS:
            listItems(&todoList);
            break;
        case MARK_COMPLETED:
        {
            int index;
            printf("Enter item number to mark as completed: ");
            scanf("%d", &index);
            markAsCompleted(&todoList, index - 1);
            break;
        }
        case REMOVE_ITEM:
        {
            int index;
            printf("Enter item number to remove: ");
            scanf("%d", &index);
            removeItem(&todoList, index - 1);
            break;
        }
        case SAVE_EXIT:
            saveToFile(&todoList, "todo.txt");
            printf("Changes saved. Exiting.\n");
            break;
        case FACTORIAL_CALCULATION:
        {
            char input[10];
            printf("Enter a positive integer to calculate its factorial: ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0; // Remove trailing newline

            if (isNumeric(input))
            {
                int num = atoi(input);
                printf("Factorial of %d is: %llu\n", num, factorial(num));
            }
            else
            {
                printf("Invalid input! Please enter a positive integer.\n");
            }
            break;
        }
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != SAVE_EXIT);

    freeToDoList(&todoList); // Clean up dynamically allocated memory

    return 0;
}
