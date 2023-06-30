#include "shell.h"

/**
  * prom_comm - function that handles
  * prompt command
  */
void prom_comm(void)
{
	char *string = NULL;
	size_t i = BUFFER_SIZE;
	ssize_t character;


	char *argv[BUFFER_SIZE];

	while (1)
	{
		prom_display();

		character = getline(&string, &i, stdin);

		if (character == -1)
		{
			perror("getline");
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

		comm_exec(argv);
	}

	free(string);
}

/**
  * path_finder - function that
  * checks the path of a command
  * @command: command whose path is to be checked
  * Return: the path to the command, else NULL
  */
char *path_finder(char *command)
{
	char command_path[BUFFER_SIZE];
	char *path = getenv("PATH");
	char *dir = strtok(path, ":");
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
		}

		dir = strtok(NULL, ": ");
	}

	if (outcome == NULL)
	{
		return (NULL);
	}

	return (outcome);
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
	size_t dir_len = strnlen(dir, BUFFER_SIZE);
	size_t command_len = strnlen(command, BUFFER_SIZE);

	size_t m = 0;
	size_t k = 0;

	if (dir_len + command_len + 2 <= BUFFER_SIZE)
	{
		for (; m < dir_len; m++)
		{
			command_path[m] = dir[m];
		}

		command_path[m++] = '/';

		for (; k < command_len; k++, m++)
		{
			command_path[m] = command[k];
		}

		command_path[m] = '\0';
		return (1);
	}

	return (0);
}

/**
  * main - entry point of the program
  * Return: 0 Always (success)
  */
int main(void)
{
	prom_comm();

	return (0);
}
