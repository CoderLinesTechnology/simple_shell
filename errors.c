#include "shell.h"

/**
 * _eputs - makes input string
 * @str: string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - prints the character c to stderr
 * @c: The character to write
 *
 * Return: On success 1, error -1,
 * errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - prints the char c to given fd
 * @c: character to print
 * @fd: The file descriptor
 *
 * Return: On success 1, error -1,
 * and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

/**
 * _putsfd - writes input string
 * @str: string to be printed
 * @fd: the filedescriptor
 *
 * Return: the number of characters put
 */
int _putsfd(char *str, int fd)
{
	int k = 0;

	if (!str)
		return (0);
	while (*str)
	{
		k += _putfd(*str++, fd);
	}
	return (k);
}
