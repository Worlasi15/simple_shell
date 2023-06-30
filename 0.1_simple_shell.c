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
  * prom_display - function that displays prompt
  *
  */
void prom_display(void)
{
	if (isatty(STDIN_FILENO))
	{
		fputs("simple_shell$", stdout);
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
	const char *delimiters = " ";
	char *token;
	int k = 0;

	token = strtok(input, delimiters);

	while (token != NULL)
	{
		argv[k] = malloc(_strnlen(token) + 1);
		strcpy(argv[k], token);
		k++;
		token = strtok(NULL, delimiters);
	}

	argv[k] = NULL;
}

/**
  * comm_exec - function thatexecutes command
  * @argv: command line arguments
  */
void comm_exec(char **argv)
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
	else if (child_pid == 0)
	{
		char *command_path = path_finder(argv[0]);

		if (command_path != NULL)
		{
			execvp(command_path, argv);
			perror("execvp");
		}
		else
		{
			fprintf(stderr, "%s: %s", argv[0], error);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}
/**
  * exec_exit - function that executes the exit command
  */
void exec_exit(void)
{
	exit(EXIT_SUCCESS);
}
