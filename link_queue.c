#include <stdio.h>
#include <stdlib.h>
#include "utility.h"


Tnode* pop_link(Lnode* head){
  if(head == NULL || head->next == NULL) return NULL;
  Lnode* temp = head->next;
  head->next = temp->next;
  Tnode* data = temp->data;
  free(temp);
  return data;
}


int push_link(Lnode* head, Tnode* data){
  if(head == NULL) return REEOR;
  Lnode *new_node = (Lnode*)malloc(sizeof(Lnode));
  if(new_node == NULL){
    return REEOR;
  }
  new_node->data = data;
  new_node->next = NULL;
  while(head->next){
    head = head->next;
  }
  head->next = new_node;
  return OK;
}


int isEmpty_link(Lnode * head){
  return (head->next == NULL);
}