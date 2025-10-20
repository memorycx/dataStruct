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

int delete(int* array,int* size,int index){
    if((*size) == 0 || index >= (*size)) return REEOR;
    for(int i = index; i < (*size) - 1; i++){
        array[i] = array[i+1];
    }
    (*size)--;
    return OK;
}

void save_array(int* array,int size,char* str,int sort){
  if(sort){
    for(int i = 0; i<= size - 1; i++){
      char temp[20];
      snprintf(temp, sizeof(temp), "%d ", array[i]);
      strncat(str, temp, 256 - strlen(str) - 1);
    }
    strcat(str, "\n");
  }else{
    for(int i = size - 1; i>=0; i--){
      char temp[20];
      snprintf(temp, sizeof(temp), "%d ", array[i]);
      strncat(str, temp, 256 - strlen(str) - 1);
    }
    strcat(str, "\n");

  }
}