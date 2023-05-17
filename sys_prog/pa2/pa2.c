#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define INPUT_LENGTH 1024
#define MAX_INPUT_LENGTH_LENGTH 200

void signal_handler(int signum) {

}

void change_directory(const char* path) {
    if (chdir(path) != 0) {
        if (errno == EACCES)
            fprintf(stderr, "cd: Permission denied\n");
        else if (errno == ENOTDIR)
            fprintf(stderr, "cd: Not a directory\n");
        else if (errno == ENOENT)
            fprintf(stderr, "cd: No such file or directory\n");
        else
            fprintf(stderr, "cd: Error occurred: %d\n", errno);
    }
}

char* find_executable(const char* cmd) {
    if (strncmp(cmd, "./", 2) == 0) {
        // "./"로 시작하는 경우, 해당 경로 그대로 사용
        return strdup(cmd);
    }
    else{
        char* path_env = getenv("PATH");
        if (path_env == NULL) {
            return NULL;
        }
        char* path_env_copy = strdup(path_env); 
        
        char* token = strtok(path_env_copy, ":");
        while (token != NULL) {
            char executable[INPUT_LENGTH];
            snprintf(executable, sizeof(executable), "%s/%s", token, cmd);
            
            if (access(executable, X_OK) == 0) {
                char* path = strdup(executable);
                free(path_env_copy);
                return path;   
            }
            
            token = strtok(NULL, ":");
        }
    }
        
    return NULL;
}

void print_error_message(const char* cmd, int err) {
    const char* err_msg = NULL;

    if (err == EACCES) {
        err_msg = "Permission denied";
    } else if (err == EISDIR) {
        err_msg = "Is a directory";
    } else if (err == ENOENT) {
        err_msg = "No such file or directory";
    } else if (err == ENOTDIR) {
        err_msg = "Not a directory";
    } else if (err == EPERM) {
        err_msg = "Operation not permitted";
    }

    if (err_msg != NULL & cmd=="head" || cmd=="tail" || cmd=="cat" || cmd=="cp" || cmd=="mv" || cmd=="rm" || cmd=="cd") {
        fprintf(stderr, "%s: %s\n", cmd, err_msg);
    } else if(err_msg == NULL && !(cmd=="head" || cmd=="tail" || cmd=="cat" || cmd=="cp" || cmd=="mv" || cmd=="rm" || cmd=="cd")) {
        fprintf(stderr, "%s: Error occurred: %d\n", cmd, err);
    }
    else{
        fprintf(stderr, "mini: command not found\n");
    }
}


int execute_cmd(char* const* args, int input_fd, int output_fd) {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return -1;
    } else if (pid == 0) {
        // Child process
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        
        execvp(args[0], args);
        fprintf(stderr, "mini: Command not found\n");
        exit(1);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
        return -1;
    }
}

int main() {
    char cmd[INPUT_LENGTH];
    int exit_status = 0;
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
    
    while (1) {
        printf("minishell> ");    
        fgets(cmd, sizeof(cmd), stdin);
        
        //\n 제거
        cmd[strcspn(cmd, "\n")] = '\0';
        
        // "exit"으로 쉘종료
        if (strcmp(cmd, "exit") == 0) {
            break;
        }
        
        // 200까지만 허용
        if (strlen(cmd) > MAX_INPUT_LENGTH_LENGTH) {
            printf("mini: cmd not found\n");
            continue;
        }
        
        // 명령어 파싱
        char* token = strtok(cmd, "|");
        int cmd_cnt = 0;
        char* cmds[INPUT_LENGTH];
        
        while (token != NULL) {
            cmds[cmd_cnt++] = token;
            token = strtok(NULL, "|");
        }
        
        int input_fd = STDIN_FILENO;
        int output_fd = STDOUT_FILENO;
        
        for (int i = 0; i < cmd_cnt; i++) {
            // 파이프 생성
            int pipe_fd[2];
            if (pipe(pipe_fd) < 0) {
                fprintf(stderr, "Pipe failed\n");
                return -1;
            }
            
            output_fd = pipe_fd[1];
            
            // 마지막 명령어
            if (i == cmd_cnt - 1) {
                output_fd = STDOUT_FILENO;
            }
            
            // 명령어 파싱
            token = strtok(cmds[i], " ");
            char* args[INPUT_LENGTH];
            int arg_cnt = 0;
            int input_flag = 0;
            int output_flag = 0;
            int input_tmp, output_tmp;
            
            while (token != NULL) {
                // input redirection
                if (strcmp(token, "<") == 0) {
                    token = strtok(NULL, " ");
                    if (token != NULL) {
                        input_tmp = open(token, O_RDONLY);
                        if (input_tmp == -1) {
                            fprintf(stderr, "mini: No such file or directory\n");
                            break;
                        }
                        input_fd = input_tmp;
                        input_flag = 1;
                    }
                    // output redirection
                } else if (strcmp(token, ">") == 0) {
                    token = strtok(NULL, " ");
                    if (token != NULL) {
                        output_tmp = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        if (output_tmp == -1) {
                            fprintf(stderr, "mini: No such file or directory\n");
                            break;
                        }
                        output_fd = output_tmp;
                        output_flag = 1;
                    }
                } else if (strcmp(token, ">>") == 0) {
                    token = strtok(NULL, " ");
                    if (token != NULL) {
                        output_tmp = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
                        if (output_tmp == -1) {
                            fprintf(stderr, "Output file open failed\n");
                            break;
                        }
                        output_fd = output_tmp;
                        output_flag = 1;
                    }
                }
                else{
                    args[arg_cnt++] = token;
                }
                token = strtok(NULL, " ");
            }
            args[arg_cnt] = NULL; // execvp 전달 위함
            
            // builtin_cmd
            if (strcmp(args[0], "cd") == 0) {
                if (arg_cnt < 2) {
                    print_error_message("cd", errno);
                    continue;
                    }
                change_directory(args[1]);
                continue;
            }

            else if(strcmp(args[0], "exit") == 0 && arg_cnt > 1) {
                    exit_status = atoi(args[1]);
                    return exit_status;
                }

            else{
                // 실행 가능한 명령어인지 확인
                char* executable_path = find_executable(args[0]);
                if (executable_path == NULL) {
                    print_error_message(args[0], errno);
                    continue;
                }
                
                // 명령어 실행
                execute_cmd(args, input_fd, output_fd);
            }
            
                close(pipe_fd[1]);
                input_fd = pipe_fd[0];

            if (input_flag) {
                close(input_fd);
                dup2(input_fd, STDIN_FILENO);
            }
            if (output_flag) {
                close(output_fd);
                dup2(output_fd, STDOUT_FILENO);
            }
        }
    }
    
    return 0;
}


