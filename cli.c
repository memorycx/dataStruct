#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


# define MAX_CMD_LEN 50

int main() {
    char input[100];  

    while (1) {
        printf("DataStructs@Qiushui> ");                     
        if (!fgets(input, sizeof(input), stdin)) break;  
        input[strcspn(input, "\n")] = '\0';   // 去掉换行符


        if (strcmp(input, "exit") == 0) {
            printf("Bye!\n");
            break;
        }
        if (strcmp(input, "help") == 0) {
            // 后续补充
            continue;
        }

        if (strcmp(input, "version") == 0) {
            printf("Mini Shell v1.0\n");
            continue;
        }

       
        pid_t pid = fork();
        if (pid == 0) {
            char cmd[MAX_CMD_LEN] = "./";
            char *argv[MAX_CMD_LEN]; 
            int argc = 0;
            int status = 0;


            char *token = strtok(input, " ");
            for(int i = 0;i < MAX_CMD_LEN;i++){
                if(token == NULL) break;
                if(i == 0 && strcmp(token, "ds") == 0){
                    status = 1;
                    token = strtok(NULL, " ");
                    continue;
                }
                if(i == 0 && strcmp(token, "ds") != 0){
                    strncpy(cmd, token, MAX_CMD_LEN - 1);
                    cmd[MAX_CMD_LEN - 1] = '\0';         
                }
                if(status == 1){
                    argv[argc++] = strcat(cmd, token);
                    status = 0;
                    token = strtok(NULL, " ");
                    continue;
                }

                argv[argc++] = token;
                token = strtok(NULL, " ");
            }


            argv[argc] = NULL;
            execvp(cmd, argv);             
            perror("命令不存在");
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            perror("fork 失败");
        }
    }

    return 0;
}

