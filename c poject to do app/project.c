// TO DO LIST APPLICATION 
#include <stdio.h>         //for input/output
#include <string.h>
#include <stdlib.h>       //for exit function
// constants
#define MAX_TASKS     100                    // Maximum no of tasks
#define TITLE_LEN     50                     // max length of the task title
#define DESC_LEN      200                    // max length of the task description
#define DATE_LEN      12                     // max length of deadline date (YYYY-MM-DD) 
#define TIME_LEN      8                      // max length of deadline time (HH:MM)
#define MIN_PRIORITY  1                      // lowest priority level
#define MAX_PRIORITY  5                      //  highest priority level
#define FILENAME     "tasks.txt"             //  file for persistent storage
// structure to represent a single task
typedef struct {
    int  id;                            // unique task id 
    char title[TITLE_LEN + 1];          // task tittle (with null terminator)
    char description[DESC_LEN + 1];     // task descripition (with null terminator)
    char deadline_date[DATE_LEN];       // deadline date
    char deadline_time[TIME_LEN];       // deadline time 
    int  priority;                      // priority level (1-5)
    int  isdone;                        // completion status (0=not done , 1=done)
 }  Task;
// Function to remove newline from end of string 
void clearNewline(char *str) {
    size_t len = strlen(str);                    // get string length
    if (len > 0 && str[len - 1] == '\n') str[len -1] = '\0';      // check if last char is '/n' // replace new line with null terminator
}
// Function to read a line safely
void readline(const char *prompt, char *buffer, int buffersize) {                                             
    printf("%s", prompt);                      // display prompt message              
    if (!fgets(buffer,buffersize,stdin)) {     // read user input                 
      puts("\n Input error!!!");                              
      exit(1);
    }
    clearNewline(buffer);                      // remove newline
 }
 // function to read an integer within a specific range , with retries on invalid inputs 
int readIntInRange(const char *prompt, int min, int max) {
  char line[80];             // buffer for input line
 int value, itemsRead;
  while (1) {
    printf("%s", prompt);      // show prompt
     if (fgets(line,sizeof(line),stdin) == NULL)  {
    printf("Input error\n");  continue; 
}
  itemsRead = sscanf(line,"%d", &value);     // try reading integer from input
    if (itemsRead == 1 && value >= min && value <= max)
         return value;                 // return valid input
    printf("Invalid input..\n"); 
  }
}
// fuction to validate deadline date format (YYYY-MM-DD)
 int isValidDate(const char *date) {
 if (strlen(date) != 10) return 0;                //must be 10 char long
 if (date[4] != '-' || date[7] != '-') return 0;   // must contain - in correct place
   int year  = atoi(date);                  // convert year
   int month = atoi(date + 5);              // convert month
   int day   = atoi(date + 8);              // convert day
 if (month < 1 || month > 12) return 0;     // month validation
 if (day < 1 || day > 31) return 0;         // day validation
 return 1;                                    // vaild date
}
// Function to validate deadline time format
int isValidTime(const char *time) {
  if (strlen(time) != 5) return 0;               // length must be exactly 5
  if (time[2] != ':') return 0;                  // must contain colon
 int hh = (time[0]-'0') * 10 + (time[1]-'0');    // extarct hours
 int mm = (time[3]-'0') * 10 + (time[4]-'0');    // extract min
  if (hh<0 || hh>23) return 0;                   // hour validation
  if (mm<0 || mm>59) return 0;                   // min validation
  return 1;                                        // valid time
}
 // Function to initialize the task array and counter.
void initTasks(Task tasks[], int maxTasks, int *taskCount, int*nextId){
  for (int i = 0; i < maxTasks; i++) {
      tasks[i] .id = 0;                     // reset task id
      tasks[i] .title[0] = '\0';            // empty title
      tasks[i] .description[0] = '\0';
      tasks[i] .deadline_date[0] = '\0';
      tasks[i] .deadline_time[0] = '\0';
      tasks[i] .priority = 0;               // reset priority
      tasks[i] .isdone = 0;                
    }
 *taskCount = 0;             // reset task count
 *nextId = 1;               // start ids from 1 
}
// Function to save task to file
void saveTasksToFile(const Task tasks[], int taskCount) {
  FILE *file = fopen(FILENAME, "w");     // open file in write mode
  if (!file) {
    printf("Error opening file for saving.\n");
    return;
  }
for (int i=0; i<taskCount; i++){         // Write all tasks to file
 fprintf(file, "%d,%s,%s,%s,%s,%d,%d\n", tasks[i].id, tasks[i].title, tasks[i].description, 
          tasks[i].deadline_date,tasks[i].deadline_time, tasks[i].priority, tasks[i].isdone);
   }
   fclose(file);                       // close file
   printf("Tasks saved in file.\n");
}
// fuction to load tasks from file
void loadTasksFromFile(Task tasks[], int maxTasks, int *taskCount, int *nextId) {
  FILE *file = fopen(FILENAME, "r");     // open file for reading
  if (!file) {
    printf("No saved tasks file found.\n");
    return;
  }
  char line[400];
  while (fgets(line, sizeof(line), file) && *taskCount < maxTasks) {
    Task t;
   if (sscanf(line, "%d,%50[^,],%200[^,],%11[^,],%5[^,],%d,%d", &t.id, t.title, t.description,
              t.deadline_date, t.deadline_time, &t.priority, &t.isdone)==7) {
      tasks[*taskCount] = t;                    // store task in array
      (*taskCount)++;                     
      if(t.id>=*nextId)                        // update next id
      *nextId = t.id + 1;          
    } 
  }
  fclose(file);
  printf("Tasks loaded from file.\n");
}
// Function to the menu
void printMenu(){
 printf("\n=================================================\n");
 printf("            SIMPLE TODO LIST APP                 \n");
 printf("=================================================\n");
 printf(" 1. Add a new task\n 2. List all tasks\n 3. Mark task as done\n");
 printf(" 4. Edit an existing task\n 5. Delete a task\n 6. Save tasks\n 7. Exit\n");
 printf("============================================\n");
}
// Function to find the idex of the task by id
int findTaskIndexbyId(const Task tasks[], int taskCount, int id){
    for (int i=0; i<taskCount; i++) if (tasks[i].id == id) return i;    // found
    return -1;                                                         // if not found
}  
// function to add a new task
void addTask(Task tasks[], int maxTasks, int *taskCount, int *nextId) {
    if (*taskCount >= maxTasks) {
     printf("Task limit reached...");
      return;
  }
  Task newTask;
  newTask.id = *nextId;
printf("\n--- Add New Task ---\n");
readline("Enter the task title: ", newTask.title, sizeof(newTask.title));
readline("Enter the description of task: ", newTask.description, sizeof(newTask.description));
while(1){
  readline("Enter deadline date(YYYY-MM-DD): ",newTask.deadline_date, sizeof(newTask.deadline_date));
  if (isValidDate(newTask.deadline_date)) break;
  printf("Invalid date format.\n");
}
while (1) {
  readline("Enter deadline time (HH:MM): ", newTask.deadline_time, sizeof(newTask.deadline_time));
  if (isValidTime(newTask.deadline_time))  break;
  printf("Invalid time format.\n");
}
newTask.priority = readIntInRange("Enter priority (1=min)-(5=max)): ", 1, 5);
newTask.isdone = 0;

tasks[*taskCount] = newTask;
(*taskCount)++;
(*nextId)++;
printf("Task added successfully with (id %d).\n", newTask.id);
}
// Function to list all tasks
void listTasks(const Task tasks[], int taskCount) {
    printf("\n--- List of Tasks ---\n");
  if(taskCount == 0) {
    printf("NO tasks found.\n");
    return;
  } 
printf("%-4s | %-5s | %-30s | %-5s | %-40s\n", "ID","DONE","TITLE","PRIORITY","DESCRIPTION");
printf("----------------------------------------------------------------------------------------------\n");
for (int i = 0; i < taskCount; i++) {
    const Task *t = &tasks[i];
  printf("%-4d | %-5s | %-30s | %-5d | %-40s\n", t->id,(t->isdone ? "Yes" : "NO"), t->title, t->priority, t->description);
 } 
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
  id = readIntInRange("Enter the id of the task to mark as done: ",1, 9999);
  index = findTaskIndexbyId(tasks,taskCount,id);
  if (index == -1) 
    printf("Task with id %d not found.\n",id);
  else { 
   tasks[index].isdone = 1;
    printf("Task with id %d marked as done.\n",id);
    saveTasksToFile(tasks, taskCount);
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
id = readIntInRange("Enter id of the task to delete: ", 1, 9999);
index = findTaskIndexbyId(tasks, *taskCount, id);
if (index == -1)
 printf("Task with id %d not found.\n", id);
else {
    for (i=index; i<(*taskCount)-1; i++) tasks[i] = tasks[i+1];  // shift tasks left
  (*taskCount)--;
  printf("Task with id %d has been deleted.\n", id);
  saveTasksToFile(tasks, *taskCount);    // saved after deleting 
  }
}
//function to edit an existing task
void editTask(Task tasks[], int taskCount) {
    int id, index, choice;
  printf("\n--- EDIT TASK ---\n");
  if (taskCount == 0) {
    printf("No task found to edit.\n");
    return;
  }  
listTasks(tasks, taskCount);
id = readIntInRange ("Enter id of the task to edit: ", 1, 9999);
index = findTaskIndexbyId(tasks, taskCount, id);
if (index == -1) {
    printf("Task with id %d not found.\n", id);
    return;
}
printf("\nEditing Task id %d\n", id);
printf("1. Edit title\n2. Edit description\n3. Edit priority\n4. Cancel\n");
choice = readIntInRange("Choose an option to edit: ", 1,4);
switch (choice) {
  case 1: readline("Enter the new title: ",tasks[index].title, sizeof(tasks[index].title));
          printf("Title updated..\n"); break;
  case 2: readline("Enter the new description: ",tasks[index].description, sizeof(tasks[index].description));
          printf("Description updated..\n");  break;       
  case 3: tasks[index].priority = readIntInRange("Enter new priority (1-5): ", 1, 5);
          printf("Priority updated..\n");  break;
  case 4: printf("Edit cancelled.\n");     break;
 }
}
// main fuction: start point of the program
int main() {
  Task tasks[MAX_TASKS];         // array to hold tasks
int taskCount, nextId, choice, Running = 1;
  initTasks(tasks, MAX_TASKS, &taskCount, &nextId );     // initialize
  loadTasksFromFile(tasks, MAX_TASKS, &taskCount, &nextId);  // load saved tasks
printf("Welcome to the simple TO-DO list APP\n");
  while (Running) {         // main loop
  printMenu();
choice = readIntInRange("Enter your choice(1-7): ", 1,7);
  switch (choice) {
      case 1: addTask(tasks, MAX_TASKS, &taskCount, &nextId); break;
      case 2: listTasks(tasks, taskCount);      break;
      case 3: markTaskAsDone(tasks, taskCount); break;
      case 4: editTask(tasks, taskCount);       break;
      case 5: deleteTask(tasks, &taskCount);    break;
      case 6: saveTasksToFile(tasks, taskCount); break;      // Manual save option
      case 7: printf("Exiting the TO-DO list app.\n"); Running = 0; break;
    }
 }
   return 0;
} 
