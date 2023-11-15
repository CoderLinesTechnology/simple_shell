#include "shell.h"

/**
 * _strlen - returns extent of a string
 * @s: string whose extent is to be check
 *
 * Return: the integer extent of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic contrast of two strangs.
 * @s1: first strang
 * @s2: second strang
 *
 * Return: negative if s2 > s1, positive if s2 < s1, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - inspects if the needle starts with haystack
 * @haystack: the string to explore
 * @needle: substring to discover
 *
 * Return: direction of succeding character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - connects two strings
 * @dest: destination buffer
 * @src: origin buffer
 *
 * Return: pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
