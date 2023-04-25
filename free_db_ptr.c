#include "shell.h"

/**
 * free_double_ptr - its the free malloced arrays
 * @str: denotes array of strings
 */
void free_double_ptr(char **str)
{
	int i = 0;

	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
