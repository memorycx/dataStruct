#include "utility.h"

int expansion(int* array,int* size){
    int newCapacity = (((*size)<<1) + (*size)) >> 1;
    array = (int*)realloc(array, newCapacity * sizeof(int));
    if(array == NULL) return REEOR;
    *size = newCapacity;
    return OK;
}


int add(int* array,int* size ,int value, int index){
    if((*size) == index){
        expansion(array,size);
    }
    array[index] = value;
    (*size)++;
    return OK;
}

int delete(int* array,int size,int index){
  size += 1;
  if(size == 0 || index >= size) return REEOR;
  for(int i = index; i < size; i++){
      array[i] = array[i+1];
  }
  return OK;
}

void save_array(int* array,int size,char*command){


  char* new_content = (char*)malloc(256 * sizeof(char));
  new_content[0] = '\0';

  for(int i = 0; i<= size - 1; i++){
    char temp[20];
    snprintf(temp, sizeof(temp), "%d ", array[i]);
    strncat(new_content, temp, 256 - strlen(new_content) - 1);
  }
  strcat(new_content, "\n");

  save(command,new_content); // save the ArraStack to tem.txt
}