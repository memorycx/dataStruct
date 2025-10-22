#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_SIZE 100
#define REEOR 0
#define OK 1


typedef struct arrayStack{
    int index;
    int* data;
    int capacity;
    int tem; // this is for push's tem value,then all functions can use the Func type
}ArrayStack;

typedef int (*Func_1)(ArrayStack *stack); 

typedef struct {
    const char *name;  
    Func_1 func;  
} CommandEntry;

int execute_command(const char *input,CommandEntry* commands);

void save(const char *line, const char *new_content);