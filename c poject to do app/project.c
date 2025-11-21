// TO DO LIST APPLICATION.
#include<stdio.h>
#include<string.h>
#define MAX 50 // maximum no of tasks
// structure for each task 
struct Task {
    char name[50];
    char date[20];
    int completed; // 0 = pending , 1 = completed
};
// declaring function
void addTask(struct Task tasks[],int*count);
void viewTasks(struct Task tasks[],int count);
void statusTask(struct Task tasks[],int count);
void deleteTask(struct Task tasks[],int*count);
int main(){
    struct Task tasks[MAX];
    int count = 0;
    int choice;
    while(1){
    printf("\n====== list Menu ======\n");
    printf("1. ADD TASK\n");
    printf("2. VIEW TASK\n");
    printf("3. MARK TASK AS COMPLETED\n");
    printf("4. DELETE TASK\n");
    printf("5. EXIT\n");
 printf("Enter your choice: ");
 scanf("%d",&choice);

 getchar(); // clear new line from buffer
 switch (choice) {

        case 1: // Add Task
            if (count < MAX) {
                printf("Enter task title: ");
                fgets(todo[count].title, sizeof(todo[count].title), stdin);
                todo[count].title[strcspn(todo[count].title, "\n")] = '\0';
                todo[count].isDone = 0;
                count++;
                printf("Task added!\n");
            } else {
                printf("Task list is full!\n");
            }
            break;

 }
}


