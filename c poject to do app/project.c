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
