#include "shell.h"

/**
 * _myenv - prints current environment
 * @info: Structure containing possible arguments. Used to maintain
 *          continues functioning prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - obtain the value of an environ variable
 * @info: Structure containing possible arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *m;

	while (node)
	{
		m = starts_with(node->str, name);
		if (m && *m)
			return (m);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Set a new environment variable,
 *             or modify an existing variable
 * @info: Structure containing potential arguments. Used to maintain
 *        continues functioning prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        continues functioning prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int m;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (m = 1; m <= info->argc; m++)
		_unsetenv(info, info->argv[m]);

	return (0);
}

/**
 * populate_env_list - occupy  env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          continues functioning prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t m;

	for (m = 0; environ[m]; m++)
		add_node_end(&node, environ[m], 0);
	info->env = node;
	return (0);
}
