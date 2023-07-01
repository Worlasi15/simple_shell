#include "shell.h"

/**
  * prom_comm - function that handles
  * prompt command
  */
void prom_comm(void)
{
	char *input = NULL;
    /*size_t n = 0;*/
    char *input_received = NULL;
    char *args[Max_Command];
    int i;


    while (1)
    {
        if (isatty(STDIN_FILENO))
	{
            write(STDOUT_FILENO, "Simple shell$ ", 14);
        }

        input_received = my_getline();

        if (input_received == NULL)
	{
            if (isatty(STDIN_FILENO))
	    {
                perror("Error");
            }
            break;
        }


        input[strcspn(input, "\n")] = '\0';

        token_izing(input, args);


       if (strcmp(args[0], "exit") == 0)
		{
			for (i = 0; args[i] != NULL; i++)
			{
				free(args[i]);
			}
			free(input);
			exit(0);
		}
	   else if (strcmp(args[0], "env") == 0)
	    {
                Env_print();
            }
	    else
	    {
                comm_exec(args);
            }
	    for (i = 0; args[i] != NULL; i++)
		{
			free(args[i]);
		}

    }

    free(input);
}

void free_memory(char **args)
{
	int i;

    for (i = 0;  args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}

void Env_print()
{
	extern char **environ;

   char ** environment_ptr = environ;

    while (*environment_ptr != NULL)
    {
        write(STDOUT_FILENO, *environment_ptr, strlen(*environment_ptr));
        write(STDOUT_FILENO, "\n", 1);
        environment_ptr++;
    }
}

/**
  * path_finder - function that
  * checks the path of a command
  * @command: command whose path is to be checked
  * Return: the path to the command, else NULL
  */
void path_finder(char **args)
{
    char *env_path, *dir_token, *path_copy = NULL, cmd_path[Max_Command];

    if (args == NULL || args[0] == NULL || args[0][0] == '/')
    {
        return;
    }

    env_path = getenv("PATH");
    if (env_path == NULL)
    {
        return;
    }

    path_copy = strdup(env_path);
    if (path_copy == NULL)
    {
        return;
    }

    dir_token = strtok(path_copy, ":");
    while (dir_token != NULL)
    {
        snprintf(cmd_path, sizeof(cmd_path), "%s/%s", dir_token, args[0]);
        if (access(cmd_path, X_OK) == 0)
        {
            free(args[0]);
            args[0] = strdup(cmd_path);
            if (args[0] == NULL)
            {
                free(path_copy);
                return;
            }
            free(path_copy);
            return;
        }
        dir_token = strtok(NULL, ":");
    }

    free(path_copy);
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
/**
  * _strcpy - function that copies string
  * @pds: pointer to the destination string
  * @pcs: pointer to the source string
  * of characters to copy
  * Return: pointer to the destination string
  */
char *_strcpy(char *pds, const char *pcs)
{
	int i;

	while (pcs[i] != '\0')
	{
		pds[i] = pcs[i];
		i++;
	}

	pds[i] = '\0';

	return (pds);
}
