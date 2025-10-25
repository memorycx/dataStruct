#include "./utility.h"
#include"./array_utility.h"


int init_queue(Array *queue){
    queue->data = (int*)malloc(MAX_SIZE * sizeof(int));
    if(queue->data == NULL) return REEOR;
    queue->index = -1;
    queue->capacity = MAX_SIZE;
    return OK;
}

int expansion_queue(Array *queue){
    if(expansion(queue->data, &queue->capacity) == REEOR) return REEOR;
    return OK;
}


int enqueue(Array *queue){
    int tem = add(queue->data, &queue->index, queue->tem, queue->index + 1);
    if(tem == REEOR) return REEOR;
    return OK;
}

int dequeue(Array *queue){
    if(delete(queue->data, queue->index, 0) == REEOR) return REEOR;
    queue->index--;
    return OK;
}

int show(Array *queue){
    for(int i = queue->index; i >= 0; i--){
        printf("%d->", queue->data[i]);
    }
    printf("\n");
    return OK;
}

int peek(Array *queue){
  if(queue->index == -1){
    printf("error: queue is empty\n");
    return 0;
  }
  printf("%d\n", queue->data[queue->index]);
  return 1;
}

int help(){
    printf("help:\n");
    //undecided
    return OK;
}

CommandEntry commands[] = {
    {"help", help},
    {"show", show},
    {"enqueue", enqueue},
    {"dequeue", dequeue},
    {"peek", peek},
    {NULL, NULL}  // it is used to mark the end of the commands array
};




int main(int argc, char const *argv[]){
    if(argc < 2){
        printf("error: not enough arguments\n");
        return 1;
    }
    Array queue;
    init_queue(&queue);


    // git data from tem.txt and push into ArraStack
    char line[256];
    read_file(line,256,"queue");

    char *token = strtok(line, " ");
    while (token != NULL) {
      int num = atoi(token);    
      queue.tem = num;
      enqueue(&queue);
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
        queue.tem = atoi(argv[i]);
        commands[num].func(&queue); // execute the command function
      }
    }else{
      commands[num].func(&queue); 
    }

    save_array(queue.data, queue.index + 1,"queue");
    return 0;
}



