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
}

