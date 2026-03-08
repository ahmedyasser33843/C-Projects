#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define TASK_LENGTH 256
#define FILE_NAME "tasks.txt"

void show_menu(void);
void load_tasks(char tasks[][TASK_LENGTH], int *count);
void save_tasks(char tasks[][TASK_LENGTH], int count);
void add_task(char tasks[][TASK_LENGTH], int *count);
void list_tasks(char tasks[][TASK_LENGTH], int count);
void delete_task(char tasks[][TASK_LENGTH], int *count);
void clear_input(void);

int main(void)
{
    char tasks[MAX_TASKS][TASK_LENGTH];
    int count = 0;
    int choice;
    
    load_tasks(tasks, &count);
    printf("Loaded %d tasks.\n", count);
    
    while (1) {
        show_menu();
        printf("Choose: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice.\n");
            clear_input();
            continue;
        }
        clear_input();
        
        if (choice == 1) {
            add_task(tasks, &count);
        } else if (choice == 2) {
            list_tasks(tasks, count);
        } else if (choice == 3) {
            delete_task(tasks, &count);
        } else if (choice == 4) {
            save_tasks(tasks, count);
            break;
        } else {
            printf("Try again.\n");
        }
    }
    
    return 0;
}

void show_menu(void)
{
    printf("\n1. Add task\n2. List tasks\n3. Delete task\n4. Save and exit\n\n");
}

void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void load_tasks(char tasks[][TASK_LENGTH], int *count)
{
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        *count = 0;
        return;
    }
    
    int i = 0;
    while (i < MAX_TASKS && fgets(tasks[i], TASK_LENGTH, fp) != NULL) {
        size_t len = strlen(tasks[i]);
        if (len > 0 && tasks[i][len - 1] == '\n') {
            tasks[i][len - 1] = '\0';
        }
        i++;
    }
    
    *count = i;
    fclose(fp);
}

void save_tasks(char tasks[][TASK_LENGTH], int count)
{
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error saving.\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", tasks[i]);
    }
    
    fclose(fp);
    printf("Saved.\n");
}

void add_task(char tasks[][TASK_LENGTH], int *count)
{
    if (*count >= MAX_TASKS) {
        printf("List is full.\n");
        return;
    }
    
    printf("Task: ");
    if (fgets(tasks[*count], TASK_LENGTH, stdin) != NULL) {
        size_t len = strlen(tasks[*count]);
        if (len > 0 && tasks[*count][len - 1] == '\n') {
            tasks[*count][len - 1] = '\0';
        }
        
        if (strlen(tasks[*count]) == 0) {
            printf("Empty task.\n");
            return;
        }
        
        (*count)++;
        printf("Added. Total: %d\n", *count);
    }
}

void list_tasks(char tasks[][TASK_LENGTH], int count)
{
    if (count == 0) {
        printf("No tasks.\n");
        return;
    }
    
    printf("\nYour tasks:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, tasks[i]);
    }
    printf("(%d total)\n", count);
}

void delete_task(char tasks[][TASK_LENGTH], int *count)
{
    if (*count == 0) {
        printf("Nothing to delete.\n");
        return;
    }
    
    list_tasks(tasks, *count);
    printf("\nDelete which task: ");
    
    int num;
    if (scanf("%d", &num) != 1) {
        printf("Bad input.\n");
        clear_input();
        return;
    }
    clear_input();
    
    if (num < 1 || num > *count) {
        printf("Bad task number.\n");
        return;
    }
    
    num--;
    for (int i = num; i < *count - 1; i++) {
        strcpy(tasks[i], tasks[i + 1]);
    }
    
    (*count)--;
    printf("Deleted. Remaining: %d\n", *count);
}