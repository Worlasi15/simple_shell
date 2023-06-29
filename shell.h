#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>

#define BUFFER_SIZE 1024
#define Max_Command 20

void print_sen(void);
int _strnlen(char *v);
void prom_display(void);
void token_izing(char **input, char *argv);
void comm_exec(char **argv, char *env);
void exec_exit(void);

#endif
