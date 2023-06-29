#include "shell.h"

/**
  * prom_comm - function that handles
  * prompt command
  * @av: command line argument
  * @env: environment variables
  */
void prom_comm(char **av, char **env)
{
	char *string = NULL;
	size_t i = 0;
	ssize_t character;
	char *argv[Max_Command];

	(void)av;

	while (1)
	{
		prom_display();

		character = getline(&string, &i, stdin);

		if (character == -1)
		{
			free(string);
			string = NULL;
			exit(EXIT_FAILURE);
		}

		if (string[character - 1] == '\n')
		{
			string[character - 1] = '\0';
		}

		token_izing(string, argv);

		if (strcmp(argv[0], "exit") == 0)
		{
			exec_exit();
		}

		comm_exec(argv, env);
	}
}

/**
  * path_finder - function that
  * checks the path of a command
  * @command: command whose path is to be checked
  * Return: the path to the command, else NULL
  */
char *path_finder(char *command)
{
	char *path = getenv("PATH");
	char *dir = strtok(path, ": ");

	char command_path[BUFFER_SIZE];
	char *outcome = NULL;

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
	}

	while (dir != NULL)
	{
		if (get_p(dir, command, command_path))
		{
			if (access(command_path, X_OK) == 0)
			{
				outcome = strdup(command_path);
				break;
			}

			dir = strtok(NULL, ": ");
		}

		return (outcome);
	}
}

/**
  * get_p - get command path
  * @dir: directory gotten from path
  * @command: command
  * @command_path: stores command path
  * Return: 1 else 0
  */
int get_p(const char *dir, const char *command,
		char *command_path)
{
	size_t dir_len = strlen(dir);
	size_t command_len = strlen(command);

	if (dir_len + command_len + 2 <= BUFFER_SIZE)
	{
		size_t m = 0;

		for (; m < dir_len; m++)
		{
			command_path[m] = command[m] = dir[m];
		}

		command_path[m++] = '/';
		size_t k = 0;

		for (; k < command_len; k++)
		{
			command_path[m + k] = command[k];
		}

		command_path[m + k] = '\0';
		return (1);
	}

	return (0);
}

/**
  * main - entry point of the program
  * @argc: the command line arguments
  * @argv: array of string holding
  * command line argument
  * @env: environment variables
  * Return: 0 Always (success)
  */
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	prom_comm(argv, env);

	return (0);
}
