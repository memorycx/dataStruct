#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_SIZE 100
#define REEOR 0
#define OK 1

typedef struct array{
    int index;
    int* data;
    int capacity;
    int tem; // this is for push's tem value,then all functions can use the Func type
}Array;




typedef struct Tnode{
  int data;
  struct Tnode *left;
  struct Tnode *right;
}Tnode;

typedef struct Lnode{
    Tnode* data;
    struct Lnode *next;
}Lnode;



typedef int (*Func_1)(Array *v); 

typedef struct {
    const char *name;  
    Func_1 func;  
} CommandEntry;

int execute_command(const char *input,CommandEntry* commands);

void save(const char *line, const char *new_content);


//向外暴露的数据结构的栈和队列，使用数组实现的
//将链表实现的队列，封装好，供内部其他数据结构使用