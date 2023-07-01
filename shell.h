#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stddef.h>

#define BUFFER_SIZE 1024
#define Max_Command 200

void print_sen(void);
int _strnlen(char *v);
void prom_display(void);
void token_izing(char *input, char **args);
char * my_getline();
void comm_exec(char **args);
void exec_exit(char *arg);
int main(void);
void path_finder(char **args);
void prom_comm(void);
int get_p(const char *dir, const char *command, char *command_path);
void free_memory(char** args);
void Env_print(void);
/*char *_strcpy(char *pds, char *pcs, int i);*/

#endif
