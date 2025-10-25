#include <stdio.h>
#include <stdlib.h>
#include "link_queue.h"




Tnode *insert(Tnode *root, int data){
  if(root == NULL){
    root = (Tnode*)malloc(sizeof(Tnode));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
  }
  else if(data <= root->data){
    root->left = insert(root->left, data);
  }
  else{
    root->right = insert(root->right, data);
  }
  return root;
}

int search(Tnode *root, int data){
  if(root == NULL){
    return 0;
  }
  else if(data == root->data){
    return 1;
  }
  else if(data <= root->data){
    return search(root->left, data);
  }
  else{
    return search(root->right, data);
  }
}

int findHeight(Tnode *root){
  if(root == NULL) return -1;
  int leftHeight = findHeight(root->left);
  int rightHeight = findHeight(root->right);
  return (leftHeight > rightHeight)? (leftHeight + 1) : (rightHeight + 1);
}

void levelOrder(Tnode *root){
  if(root == NULL) return;
  Lnode *queue = (Lnode*)malloc(sizeof(Lnode));
  push_link(queue, root);
  while(!isEmpty_link(queue)){
    Tnode *temp = pop_link(queue);
    if(temp == NULL) break;
    printf("%d ",temp->data);
    if(temp->left != NULL) push_link(queue, temp->left);
    if(temp->right != NULL) push_link(queue, temp->right);
  }
}

void inOrder(Tnode *root){
  if(root == NULL) return;
  inOrder(root->left);
  printf("%d ",root->data);
  inOrder(root->right);
}


void printTree(Tnode* node, const char* prefix, int isLast) {


    printf("%s", prefix);
    printf(isLast ? "└── " : "├── ");
    if(node == NULL){
        printf("NULL\n");
        return;
    }
    printf("%d\n", node->data);

    char* newPrefix = (char*)malloc(strlen(prefix) + 4);
    strcpy(newPrefix, prefix);
    strcat(newPrefix, isLast ? "    " : "│   ");

    printTree(node->left, newPrefix, 0);
    printTree(node->right, newPrefix, 1);

    free(newPrefix);
}

// 封装打印函数
void show(Tnode* root) {
  printf("\n\n每个结点下的第一个孩子是左孩子，第二个孩子是右孩子\n"
  "each node has two child,the first is left child,the second is right child\n\n");

  if (!root) {
      printf("空树\n");
      return;
  }
  printf("%d\n", root->data);
  printTree(root->left, "", 0);
  printTree(root->right, "", 1);
}


int main(int argc, char const *argv[]){

  Tnode *root = NULL;

  if(argc < 2){
    printf("error: not enough arguments\n");
    return 1;
  }

  if(strcmp(argv[1], "help") == 0){
    printf("insert <data1> <data2>... <dataN>\n"
    "search <data>\n"
    "height\n"
    "levelOrder\n"
    "inOrder\n"
    "show\n");
    return 0;
  }



  char line[256];

  read_file(line,256,"tree");
  char *token = strtok(line, " ");
  while (token != NULL) {
    int num = atoi(token);    
    root = insert(root, num);
    token = strtok(NULL, " ");  
  }

  if(strcmp(argv[1], "insert") == 0){
    if(argc < 3){
      printf("error: not enough arguments\n");
      return 1;
    }
    for(int i = 2; i < argc; i++){
      root = insert(root, atoi(argv[i]));
      strcat(line, argv[i]);
      strcat(line, " ");
    }
    strcat(line, "\n");
    save("tree", line);
  }

  else if(strcmp(argv[1], "search") == 0){
    if(argc < 3){
      printf("error: not enough arguments\n");
      return 1;
    }
    if(search(root, atoi(argv[2]))) printf("found\n");
    else printf("not found\n");
  }

  else if(strcmp(argv[1], "height") == 0){
    printf("height: %d\n", findHeight(root));
  }

  else if(strcmp(argv[1], "levelOrder") == 0){
    levelOrder(root);
  }

  else if(strcmp(argv[1], "inOrder") == 0){
    inOrder(root);
  }

  else if(strcmp(argv[1], "show") == 0){
    show(root);
  }

  else{
    printf("error: invalid command\n");
    return 1;
  }

  return 0;
}