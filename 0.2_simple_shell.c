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
	char *path = getenv("PATH");
	char *dir = strtok(path, ":");
	char *outcome = NULL;
	size_t dir_len, command_path_len;
	char *command_path = NULL;

	if (path == NULL)
	{
		return (NULL);
	}
	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
	}

	while (dir != NULL)
	{
		dir_len = _strnlen(dir);
		command_path_len = dir_len + 2;

		if (command_path_len > BUFFER_SIZE)
		{
			return (NULL);
		}

		command_path = malloc(command_path_len);

		if (command_path == NULL)
		{
			return (NULL);
		}

		snprintf(command_path, command_path_len, "%s/%s", dir, command);

		if (access(command_path, X_OK) == 0)
		{
			outcome = (strdup(command_path));
			break;
		}

		free(command_path);
		dir = strtok(NULL, ": ");
	}

	free(command_path);
	return (outcome);
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
