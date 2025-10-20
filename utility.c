#include "utility.h"

int execute_command(const char *input,CommandEntry* commands) {
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(input, commands[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

void save(const char *line, const char *new_content) {
    FILE *src = fopen("./data.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    if (src == NULL || tmp == NULL) {
        perror("文件打开失败");
        return;
    }
    char buffer[256];
    int status = 0;
    while (fgets(buffer, sizeof(buffer), src) != NULL) {
      char temp[256];
      strncpy(temp, buffer, sizeof(temp)-1);
      temp[strcspn(temp, "\r\n")] = '\0'; 


      if(status == 1){
        fputs(new_content, tmp);   
        break;
      }
      if (strcmp(temp, line) == 0) {
          status = 1;
          fputs(buffer, tmp);    
          continue;
      } else {
          fputs(buffer, tmp);     // 复制其他行
      }
    }
    if (status == 1) {
        while (fgets(buffer, sizeof(buffer), src) != NULL) {
            fputs(buffer, tmp);
        }
    }
    fclose(src);
    fclose(tmp);
    // 替换原文件
    remove("./data.txt");
    rename("temp.txt", "./data.txt");
}
