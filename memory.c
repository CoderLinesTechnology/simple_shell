#include "shell.h"

/**
 * bfree - releases a pointer and NULLs value to address
 * @ptr: address of pointer to release
 *
 * Return: 1 if released, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
