#include "shell.h"

/**
 * get_file_path - Get a file's absolute path
 * @file_name: argument name
 *
 * Return: absolute path
 */
char *get_file_path(char *file_name)
{
	char *path = getenv("PATH"), *result;
	char *full_path;

	if (check_full_path(file_name) && access(file_name, X_OK) == 0)
	{
		result = strdup(file_name);
		if (result == NULL)
		{
			perror("Error: strdup failed");
			return (NULL);
		}
		return (result);
	}
	if (!path)
	{
		perror("Path not found");
		return (NULL);
	}

	full_path = get_file_loc(path, file_name);

	if (full_path == NULL)
	{
		perror("Absolute path not found");
		return (NULL);
	}
	return (full_path);
}

/**
 * get_file_loc - get file executable path
 * @path: absolute path parameter
 * @file_name: executable file
 *
 * Return: path to executable file
 */
char *get_file_loc(char *path, char *file_name)
{
	char *path_copy, *token;
	struct stat file_path;
	char *path_buffer = NULL;

	path_copy = strdup(path);
	token = strtok(path_copy, ":");

	while (token)
	{
		if (strlen(token) > 0)
		{
			path_buffer = malloc(strlen(token) + strlen(file_name) + strlen("/") + 1);
			if (!path_buffer)
			{
				perror("Error: malloc failed");
				free(path_copy);
				exit(EXIT_FAILURE);
			}

			if (file_name != NULL)
			{
			_strcpy(path_buffer, token);
			_strcat(path_buffer, "/");
			_strcat(path_buffer, file_name);
			_strcat(path_buffer, "\0");

			if (stat(path_buffer, &file_path) == 0 && access(path_buffer, X_OK) == 0)
			{
				free(path_copy);
				return (path_buffer);
			}
			}
			free(path_buffer);
			path_buffer = NULL;
			}

			token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * check_full_path - check if the file is absolute
 * @str: filename to be checked
 *
 * Return: 0 if yes or 1 if otherwise
 */
int check_full_path(const char *str)
{
	if (str != NULL && str[0] == '/')
		return (1);

	return (0);
}
