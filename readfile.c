#include "header/datano.h"

/**
 * tokenize - allocate enough space for the array and fill it with args
 * @str: string to count from
 * @size: number of split
 * Return: array of args
 */
char **tokenize(char *str, int size)
{
	int i = 0;
	char **args = malloc(sizeof(char *) * (size + 1)), *tok, *del = " ";

	tok = strtok(str, del);
	while (tok)
	{
		args[i++] = strdup(tok);
		tok = strtok(NULL, del);
	}
	args[i] = NULL;
	return (args);
}
/**
 * free2D - free 2d array
 * @args: array of arrgs to free
 */
void free2D(char **args)
{
	int i = 0;

	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
}

/**
 * countargs - count number of argument and remove spaces at the start
 * @str: string to count from
 * @c: delimitor
 * Return: number of argument
 * if there is only spaces in the string remove spaces and return 0
 */
int countargs(char **str, char c)
{
	while (**str == ' ')
		(*str) += 1;
	int num = 1;
	char *ptr = *str;

	if (*ptr == '\0')
		return (0);
	while (*ptr != '\0')
	{
		if (*ptr == c && *(ptr + 1) != c && *(ptr + 1) != '\0')
			num++;
		ptr++;
	}
	return (num);
}
