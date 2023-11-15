#include "shell.h"

/**
 * is_quote_balanced - Checks if quotes are balanced in the input string.
 * @str: The input string to check.
 *
 * Return: 1 if quotes are balanced, 0 otherwise.
 */
int is_quote_balanced(const char *str)
{
	int in_quote = 0;
	char quote_char = '\0';

	while (*str) {
		if ((*str == '"' || *str == '\'') && in_quote == 0) {
			in_quote = 1;
			quote_char = *str;
		} else if (*str == quote_char) {
			in_quote = 0;
			quote_char = '\0';
		}
		str++;
	}

	return in_quote == 0;
}

/**
 * display_prompt - Displays the shell prompt if it's an interactive shell.
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "Natty$ ", 7);
}

/**
 * read_input - Reads a line of input from the user.
 *
 * Return: The input string.
 */
char *read_input(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	ssize_t nread;

	/*if (nread == -1)
	{
		exit(EXIT_FAILURE);
	}*/
	do {
		nread = getline(&buffer, &buffer_size, stdin);

		/*
		 * Check if the line ends with a backslash,
		 * indicating line continuation
		 */
		while (nread > 0 && buffer[nread - 1] == '\\') {
			char *line = NULL;
			size_t line_size = 0;

			/* Read the next line */
			ssize_t additional_read = getline(&line, &line_size, stdin);

			/* Trim newline character from the additional line */
			if (additional_read > 0 && line[additional_read - 1] == '\n') {
				line[additional_read - 1] = '\0';
			}

			/* Append the additional line to the buffer */
			buffer = realloc(buffer, buffer_size + additional_read);
			strcat(buffer, line);

			/* Update buffer size */
			buffer_size += additional_read;

			/* Free the additional line memory */
			free(line);

			/* Read the next line (if needed) */
			nread = getline(&buffer, &buffer_size, stdin);
		}
	} while (nread > 0 && !is_quote_balanced(buffer));

	/* Trim newline character from the final buffer */
	if (nread > 0 && buffer[nread - 1] == '\n') {
		buffer[nread - 1] = '\0';
	}


	return (buffer);
}

/**
 * parse_input - Parses the input string into an array of strings.
 * @input: The input string to be parsed.
 *
 * Return: An array of strings.
 */
char **parse_input(char *input)
{
	char *token;
	char **array = malloc(sizeof(char *) * 1024);
	int i;

	if (array == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}

	i = 0;
	token = strtok(input, " \n");
	while (token)
	{
		array[i] = token;
		token = strtok(NULL, " \n");
		i++;
	}
	array[i] = NULL;

	return (array);
}

/**
 * execute_command - Executes a command by forking a child process.
 * @array: An array of strings representing the command and its arguments.
 */
void execute_command(char **array)
{
	char *path = get_file_path(array[0]);
	pid_t child_pid;
	int status;

	if (path == NULL)
	{
		fprintf(stderr, "Error: Command not found\n");
		return;
	}
	if (strcmp(array[0], "env") == 0)
	{
		handle_env();
		free(path);
		return;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Failed to create pid");
		free(path);
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		if (execve(path, array, NULL) == -1)
		{
			perror("Couldn't execute");
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}


/**
 * main - Main function for the shell.
 * @argc: Argument count to main (unused).
 * @argv: Array of argument values (unused).
 *
 * Return: 0 for success and -1 for failure.
 */
int main(int argc, char *argv[])
{
	char *buffer = NULL;
	char **array;

	(void)argc, (void)argv;

	while (1)
	{
		display_prompt();
		buffer = read_input();
		if (handle_exit(buffer))
		{
			free(buffer);
			break;
		}
		array = parse_input(buffer);
		execute_command(array);

		cleanup(array, buffer);
	}

	return (0);
}
