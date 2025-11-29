// TO DO LIST APPLICATION 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// constants
#define MAX_TASKS     100   //Maximum no of tasks
#define TITLE_LEN     50    // max length of the task title
#define DESC_LEN      200   //max length of the task description 
#define MIN_PRIORITY  1     //lowest priority level
#define MAX_PRIORITY  5     //highest priority level
// structure to represent a single task
typedef struct {
    int  id;                            // unique task id 
    char title[TITLE_LEN + 1];          // task tittle (with null terminator)
    char description[DESC_LEN + 1];     // task descripition (with null terminator)
    int  priority;                      // priority level (1-5)
    int  isdone;                        // completion status (0=not done , 1=done)
 }  Task;
// Function to remove trailing newline from a string 
void clearNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len -1] = '\0';
 }
// Function to read a input line into a buffer with a prompt
void readline(const char *prompt, char *buffer, int buffersize) {
    printf("%s", prompt);
    if (!fgets(buffer,buffersize,stdin)) {
        puts("\n Input error!!!");
        exit(1);
    }
    clearNewline(buffer);
 }
 // function to read an integer within a specific range , with retries on invalid inputs 
int readIntInRange(const char *prompt, int min, int max) {
    char line[80];  // buffer for input line
    int value, itemsRead;
    while (1){
        printf("%s", prompt);
    if (fgets(line,sizeof(line),stdin) == NULL) {
        printf("Input error.\n");   continue;
    }
    itemsRead = sscanf(line,"%d", &value);
    if (itemsRead != 1) {
        printf("Invalid input..");  continue;
    }
    if (value < min || value > max){
        printf("Out of range.");    continue;
    }
    return value;
  }
}
// Function to initialize the task array and counter.
void initTasks(Task tasks[], int maxTasks, int *taskCount, int*nextId){
    for (int i = 0; i < maxTasks; i++) {
        tasks[i] .id = 0;
        tasks[i] .title[0] = '\0';
        tasks[i] .description[0] = '\0';
        tasks[i] .priority = 0;
        tasks[i] .isdone = 0;
    }
 *taskCount = 0;             // reset task count
 *nextId = 1;               // start ids from 1 
}
// Function to the menu
void printMenu(){
 printf("\n=============================================\n");
 printf("          SIMPLE TODO LIST APP               \n");
 printf("=============================================\n");
 printf(" 1. Add a new task\n 2. List all tasks\n 3. Mark task as done\n");
 printf(" 4. Edit an exiting task\n 5. Delete a task\n 6. Exit\n");
 printf("============================================\n");
}
// function to add a new task
void addTask(Task tasks[], int maxTasks, int *taskCount, int *nextId) {
    Task newTask;
    char priorityPrompt[80];
    if (*taskCount >= maxTasks) {
     printf("Task limit reached...");
        return;
  }
printf("\n--- Add New Task ---\n");
newTask.id = *nextId;
readline("Enter the task title: ", newTask.title, sizeof(newTask.title));
readline("Enter the description of task: ", newTask.description, sizeof(newTask.description));
snprintf(priorityPrompt, sizeof(priorityPrompt), "Enter priority (%d = lowest, %d = highest): ",MIN_PRIORITY, MAX_PRIORITY);
newTask.priority = readIntInRange(priorityPrompt,MIN_PRIORITY, MAX_PRIORITY);
newTask.isdone = 0;
tasks[*taskCount] = newTask;
(*taskCount)++;
(*nextId)++;
printf("Task added successfully with id %d.\n", newTask.id);
}
// Function to list all tasks
void listTasks(const Task tasks[], int taskCount) {
    printf("\n--- List of Tasks ---\n");
  if(taskCount == 0) {
    printf("NO tasks found.\n");
    return;
  } 
printf("%-4s | %-5s | %-50s | %-5s | %s\n", "ID","DONE","TITLE","PRIORITY","DESCRIPTION");
printf("----------------------------------------------------------------------------------------------\n");
for (int i = 0; i < taskCount; i++) {
  const Task *t = &tasks[i];
  printf("%-4d | %-5s | %-50s | %-5d | %s\n", t->id,(t->isdone ? "Yes" : "NO"), t->title, t->priority, t->description);
 } 
}
// Function to find the idex of the task by id
int findTaskIndexbyId(const Task tasks[], int taskCount, int id){
    for (int i=0; i<taskCount; i++) if (tasks[i].id == id) return i;
    return -1;      // if not found
}
// Function to mark a task as done
void markTaskAsDone(Task tasks[], int taskCount) {
    int id, index;
    printf("\n--- Mark as Done ---\n");
  if (taskCount == 0) {
    printf("No task found to mark..\n");
    return;
  }
  listTasks(tasks,taskCount);
  id = readIntInRange("Enter the id of the task to mark as done: ",1, 1000);
  index = findTaskIndexbyId(tasks,taskCount,id);
  if (index == -1) 
  printf("Task with id %d not found.\n",id);
  else { 
   tasks[index].isdone = 1;
    printf("Task with id %d marked as done.\n",id);
   }
 }
// function to delete a task by id 
void deleteTask(Task tasks[], int *taskCount){
  int id, index, i;
  printf("\n--- Delete Task ---\n");
 if (*taskCount == 0) {
    printf("No tasks found to delete.\n");
    return;
 }
listTasks(tasks, *taskCount);
id = readIntInRange("Enter id of the task to delete: ", 1, 1000);
index = findTaskIndexbyId(tasks, *taskCount, id);
if (index == -1)
 printf("Task with id %d not found.\n", id);
else {
    for (i=index; i<(*taskCount)-1; i++) tasks[i] = tasks[i+1];  // shift tasks left
  (*taskCount)--;
  printf("Task with id %d has been deleted.\n", id);  
  }
}
//function to edit an existing task
void editTask(Task tasks[], int taskCount) {
    int id, index, choice;
    char priorityPrompt[80];
  printf("\n--- EDIT TASK ---\n");
  if (taskCount == 0) {
    printf("No task found to edit.\n");
    return;
  }  
listTasks(tasks, taskCount);
id = readIntInRange ("Enter id of the task to edit: ", 1, 1000);
index = findTaskIndexbyId(tasks, taskCount, id);
if (index == -1) {
    printf("Task with id %d not found.\n", id);
    return;
}
printf("\nEditing Task id %d\n", id);
printf("1. Edit title\n 2. Edit descripition\n 3. Edit priority\n 4. Cancle\n");
choice = readIntInRange("choose an option to edit: ", 1,4);
switch (choice) {
  case 1: readline("Enter the new title: ",tasks[index].title, sizeof(tasks[index].title));
          printf("Title updated..\n"); break;
  case 2: readline("Enter the new description: ",tasks[index].description, sizeof(tasks[index].description));
          printf("Descripition updated..\n");  break;
  case 3: snprintf(priorityPrompt, sizeof(priorityPrompt),"Enter the new Priority (%d = lowest, %d= highest): ", MIN_PRIORITY,MAX_PRIORITY);
          printf("Priority updated..\n"); break;
  case 4: default: printf("Edit canclled.\n"); break;
 }
}
// main fuction: start point of the program
int main() {
  Task tasks[MAX_TASKS];         // array to hold tasks
  int taskCount, nextId, userchoice, Running = 1;
  initTasks(tasks, MAX_TASKS, &taskCount, &nextId );     // initialize
  printf("Welcome t the simple TO-DO list APP\n");
   while (Running) {         // main loop
    printMenu();
    userchoice = readIntInRange("Enter your choice(1-6): ", 1,6);
    switch (userchoice) {
        case 1: addTask(tasks, MAX_TASKS, &taskCount, &nextId); break;
        case 2: listTasks(tasks, taskCount);      break;
        case 3: markTaskAsDone(tasks, taskCount); break;
        case 4: editTask(tasks, taskCount);       break;
        case 5: deleteTask(tasks, &taskCount);    break;
        case 6: printf("Exiting the TO-DO list app.\n"); Running = 0; break;
    }
 }
    return 0;
}
