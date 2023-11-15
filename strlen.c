#include "shell.h"

/**
*_strlen - String Length
*@s: first number param
*Return: the length
*/

int _strlen(char *s)
{
	int i = 0;

	for (; *s; s++)
		i++;
	return (i);
}
