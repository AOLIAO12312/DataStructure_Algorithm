#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define IN 1
#define OUT 0
#define MAX_CMD 10      // 最大命令数量
#define BUFFSIZE 255    // 输入最大命令字符数
#define MAX_CMD_LEN 100 // 每条命令的最大长度

/* 全局变量 */
int argc;            // 命令行的有效参数个数
char *argv[MAX_CMD]; // 参数指针数组
char command[MAX_CMD][MAX_CMD_LEN]; // 参数二维数组
char buf[BUFFSIZE];    // 接受键盘输入的参数数组
int commandNum = 0;    // 已经输入指令数目
char history[MAX_CMD][BUFFSIZE];    // 存放历史命令

/* 函数声明 */
int input(char buf[]);
void analysis(char *buf);
void work(int argc, char *argv[]);
int printHistory(char command[MAX_CMD][MAX_CMD_LEN]);
int helpCd(int argc);

/* 函数实现 */
int printHistory(char command[MAX_CMD][MAX_CMD_LEN]) {
    int n = 0;
    // 检查是否有参数
    if (command[1][0] != '\0') {
        n = atoi(command[1]);
        if (n <= 0) {
            printf("请输入有效的数字参数\n");
            return 0;
        }
    } else {
        // 默认显示全部历史命令
        n = commandNum;
    }
    
    // 限制最大显示数量
    if (n > commandNum) {
        n = commandNum;
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\n", i + 1, history[i]);
    }
    return 0;
}

int input(char buf[]) {
    // buf数组初始化
    memset(buf, 0x00, BUFFSIZE);
    if (fgets(buf, BUFFSIZE, stdin) == NULL) {
        // 处理EOF (Ctrl+D)
        printf("\n");
        exit(0);
    }
    
    // 去除fgets带来的末尾\n字符
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    }
    
    // 返回字符数量(不包括终止符)
    return (int)strlen(buf);
}

void analysis(char *buf) {
    // 初始化argv和command数组
    for (int i = 0; i < MAX_CMD; i++) {
        argv[i] = NULL;
        for (int j = 0; j < MAX_CMD_LEN; j++)
            command[i][j] = '\0';
    }
    argc = 0;
    
    // 构建command数组
    int len = strlen(buf);
    int i, j;
    for (i = 0, j = 0; i < len; ++i) {
        if (buf[i] != ' ') {
            command[argc][j++] = buf[i];
        } else {
            if (j != 0) {
                command[argc][j] = '\0';
                ++argc;
                j = 0;
            }
        }
    }
    if (j != 0) {
        command[argc][j] = '\0';
        ++argc;
    }
    
    // 构建argv数组
    argc = 0;
    int flg = OUT;
    for (i = 0; buf[i] != '\0'; i++) {
        if (flg == OUT && !isspace(buf[i])) {
            flg = IN;
            argv[argc++] = buf + i;
        } else if (flg == IN && isspace(buf[i])) {
            flg = OUT;
            buf[i] = '\0';
        }
    }
    argv[argc] = NULL;
}

void work(int argc, char* argv[]) {
    pid_t pid;
    /* 识别shell内置命令 */
    if (strcmp(command[0], "cd") == 0) {
        int res = helpCd(argc);
        if (!res) 
            printf("cd指令输入错误!\n");
    } else if (strcmp(command[0], "history") == 0) {
        printHistory(command);
    } else if (strcmp(command[0], "exit") == 0) {
        exit(0);
    } else {
        switch(pid = fork()) {
            // fork子进程失败
            case -1:
                printf("创建子进程未成功");
                return;
            // 处理子进程
            case 0:
                execvp(argv[0], argv);
                // 如果命令成功执行则不会执行以下两条语句，如果子进程未被成功执行, 则报错
                printf("%s: 命令输入错误\n", argv[0]);
                exit(1);
            // 主进程
            default: {
                int status=0;
                waitpid(pid, &status, 0);    // 等待子进程返回
                int err = WEXITSTATUS(status); // 读取子进程的返回码
                if (err) { 
                    printf("Error: %s\n", strerror(err));
                }
            }
        } // switch 结束
    }
}
int helpCd(int argc) {
    if (argc != 2) {
        return 0; // 错误参数数量
    }
    
    if (chdir(command[1]) != 0) {
        perror("cd");
        return 0;
    }
    
    return 1; // 执行成功
}

int main() {
    while(1) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s> ", cwd);
        } else {
            printf("ysh> ");
        }
        
        // 接受来自键盘的输入
        if (input(buf) == 0)
            continue;
            
        // 存入历史命令数组(处理循环存储)
        strcpy(history[commandNum % MAX_CMD], buf);
        commandNum++;
        
        // 分析命令，构建指令数组，指令参数数组
        analysis(buf);
        
        // 执行指令
        work(argc, argv);
        
        // 重置参数计数
        argc = 0; // 修复中文分号问题
    }
    return 0;
}