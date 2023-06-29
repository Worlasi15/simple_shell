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
		lgth++;

	return (lgth);
}

/**
  * prom_display - function that displays prompt
  *
  */
void prom_display(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "simple_shell$", 15);
	}
}

/**
  * token_izing - function that tokenizes
  * string input
  * @input: string input to be tokenized
  * @argv: array to store tokens
  */
void token_izing(char *input, char **argv)
{
	int k = 0;
	char *token = strtok(input, " ");

	while (token)
	{
		k++;
		token = strtok(NULL, " ");
	}
	argv[k] = NULL;
}

/**
  * comm_exec - function thatexecutes command
  * @argv: command line arguments
  * @env: environment variables
  */
void comm_exec(char **argv, char *env[])
{
	pid_t child_pid;
	int status;
	char error[] = "No such file or directory\n";

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		char *command_path = check_path(argv[0]);

		if (command_path != NULL)
		{
			if (execve(command_path, argv, env) == -1)
			{
				perror("execve");
			}
			free(command_path);
		}
		else
		{
			write(STDERR_FILENO, argv[0], _strnlen(argv[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, error, _strnlen(error));
			exit(EXIT_FAILURE);
		}
	}

	wait(&status);
}

/**
  * exec_exit - function that executes the exit command
  */
void exec_exit(void)
{
	exit(EXIT_SUCCESS);
}
