#include "shell.h"

/**
 * handle_env - Handles the 'env' built-in command.
 */
void handle_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}


/**
 * handle_exit - Function to handle the exit command.
 * @command: cammand parameter
 * Return: true if the exit command is encountered, false otherwise.
 */
bool handle_exit(char *command)
{
	char *token = strtok(command, "\n");

	if (token != NULL && strcmp(token, "exit") == 0)
	{
		return (true);
	}

	return (false);
}
