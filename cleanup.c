#include "shell.h"

/**
 * cleanup - Frees memory allocated for array and buffer.
 * @array: Array of strings to be freed.
 * @buffer: Buffer to be freed.
 */

void cleanup(char **array, char *buffer)
{
	if (array != NULL)
		free(array);
	free(buffer);
}
