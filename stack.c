#include "./utility.h"
#include"./array_utility.h"


int initStack(Array *stack){
    stack->data = (int*)malloc(MAX_SIZE * sizeof(int));
    if(stack->data == NULL) return REEOR;
    stack->index = -1;
    stack->capacity = MAX_SIZE;
    return OK;
}

int expansion_stack(Array *stack){
    if(expansion(stack->data, &stack->capacity) == REEOR) return REEOR;
    return OK;
}


int push(Array *stack){
    int tem = add(stack->data, &stack->index, stack->tem, stack->index + 1);
    if(tem == REEOR) return REEOR;
    return OK;
}

int pop(Array *stack){
    if(delete(stack->data, stack->index, stack->index) == REEOR) return REEOR;
    stack->index--;
    return OK;
}

int show(Array *stack){
    for(int i = stack->index; i >= 0; i--){
        printf("%d->", stack->data[i]);
    }
    printf("\n");
    return OK;
}

int help(){
    printf("help:\n");
    //undecided
    return OK;
}

CommandEntry commands[] = {
    {"help", help},
    {"show", show},
    {"push", push},
    {"pop", pop},
    {NULL, NULL}  // it is used to mark the end of the commands array
};




int main(int argc, char const *argv[]){
    if(argc < 2){
        printf("error: not enough arguments\n");
        return 1;
    }
    Array stack;
    initStack(&stack);


    // git data from tem.txt and push into ArraStack
  
    char line[256];
    read_file(line, 256, "stack");
    char *token = strtok(line, " ");
    while (token != NULL) {
      int num = atoi(token);    
      stack.tem = num;
      push(&stack);
      token = strtok(NULL, " ");  
    }

    int num = execute_command(argv[1],commands); // for find the command
    if(num == -1){
        printf("error: command not found\n");
        return 1;
    }

    printf("command: %s\n", commands[num].name);
    if(num == 2){
      for(int i = 2;i < argc;i++){
        stack.tem = atoi(argv[i]);
        commands[num].func(&stack); // execute the command function
      }
    }else{
      commands[num].func(&stack); 
    }

    save_array(stack.data, stack.index + 1,"stack");
    return 0;
}



