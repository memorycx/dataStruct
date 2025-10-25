#include <stdio.h>
#include <stdlib.h>
#include "link_queue.h"


int find_max(Tnode* root){
  while(root->right) root = root->right;
  return root->data;
}

int find_min(Tnode* root){
  while(root->left) root = root->left;
  return root->data;
}

Tnode* delete_Tnode(Tnode* root, int data){
  if(root == NULL) return NULL;
  if(data < root->data) root->left = delete_Tnode(root->left, data);
  else if(data > root->data) root->right = delete_Tnode(root->right, data);
  else{
    // in here we have found the node to be deleted

    //case 1 : no chile
    if(root->left == NULL && root->right == NULL){
      free(root);
      root = NULL;
    }

    //case 2 : one child
    else if(root->left == NULL){
      Tnode* temp = root;
      root = root->right;
      free(temp);
    }

    else if(root->right == NULL){
      Tnode* temp = root;
      root = root->left;
      free(temp);
    }
    

    //case 3 : two children
    else{
      // find the max value in the left subtree and replace the node's value with it
      root->data = find_max(root->left);
      root = delete_Tnode(root->left, root->data);
    }
  }
  return root;
}


// 这里如果想要多重去重，需要哈希表来解决数量问题
// 目前不支持BST中存在数据重复的情况
char* delete_text(char *line,int size, const char *data) {
  char *new_line = (char*)malloc(sizeof(char) * 256);
  int j = 0;
  for(int i = 0; i < size; i++){
    if(line[i] != data[0]){
      new_line[j] = line[i];
      j++;
    }

  }
  new_line[j] = '\0';
  return new_line;

}

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
  read_file(line, 256, "tree");

  char tem_line[256];
  strncpy(tem_line, line, 256);
  line[255] = '\0';
  tem_line[255] = '\0';

  char *token = strtok(tem_line, " ");

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

  else if(strcmp(argv[1], "delete") == 0){
    printf("delete <data>\n");
    if(argc < 3){
      printf("error: not enough arguments\n");
      return 1;
    }
    root = delete_Tnode(root, atoi(argv[2]));
    char *new_line = delete_text(line,sizeof(line), argv[2]);
    strcat(new_line, "\n");
    printf("new_line: %s\n", new_line);
    save("tree",new_line);
    free(new_line);
  }

  else{
    printf("error: invalid command\n");
    return 1;
  }

  return 0;
}