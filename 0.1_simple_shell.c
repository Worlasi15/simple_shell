#include "shell.h"


/**
  * _strnlen - function that calculates
  * the length of a string
  * @v: string
  * Return: the length of the string
  */
int _strnlen(char *v)
{
	size_t lgth = 0;

	while (*v++)
	{
		lgth++;
	}

	return (lgth);
}

/**
  * token_izing - function that tokenizes
  * string input
  * @input: string input to be tokenized
  * @args: array to store tokens
  */
void token_izing(char *input, char **args)
{
	int f = 0;
	char *token;

	token = strtok(input, " ");

	while (token != NULL && f < Max_Command - 1)
	{
		args[f++] = strdup(token);
		token = strtok(NULL, " ");
	}
	args[f] = NULL;
}

/**
  * comm_exec - function thatexecutes command
  * @args: command line arguments
  */
void comm_exec(char **args)
{
    pid_t child = fork();
    if (child == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child == 0)
    {
        path_finder(args);

        if (execve(args[0], args, NULL) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int status;
        if (waitpid(child, &status, 0) == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
}

/**
  * exec_exit - function that executes the exit command
  */
void exec_exit(void)
{
	int status;
	char **args = 0;

if (args[1] == NULL)
{

        exit(0);
    }
else if (args[2] == NULL)
{
        status = atoi(args[1]);
        exit(status);
    }
}
