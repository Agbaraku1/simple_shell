#include "shell.h"

/**
 * find_env - it finds given env_ var in linked list
 * @env: environmental variable linked list
 * @str: variable name
 * Return: idx of node in linked list
 */
int find_env(list_t *env, char *str)
{
	int j = 0, index = 0;

	while (env != NULL)
	{
		j = 0;
		while ((env->var)[j] == str[j])
			j++;
		if (str[j] == '\0')
			break;
		env = env->next;
		index++;
	}
	if (env == NULL)
		return (-1);
	return (index);
}

/**
 * _unsetenv -it helps remove node in environmental linked list
 * @env: linked list
 * @str: user's typed in command (e.g. "unsetenv MAIL")
 * Return: 0 on success
 */
int _unsetenv(list_t **env, char **str)
{
	int index = 0, j = 0;

	if (str[1] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		free_double_ptr(str);
		return (-1);
	}
	index = find_env(*env, str[1]);
	free_double_ptr(str);
	if (index == -1)
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	j = delete_nodeint_at_index(env, index);
	if (j == -1)
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	return (0);
}

/**
 * _setenv - it creates or modify existing env_ var in linked list
 * @env: linked list
 * @str: uses user's typed in command (e.g. "setenv USER Superman")
 * Return: 0 on success, 1 on fail
 */
int _setenv(list_t **env, char **str)
{
	int index = 0, j = 0;
	char *cat;
	list_t *holder;

	if (str[1] == NULL || str[2] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		free_double_ptr(str);
		return (-1);
	}
	cat = _strdup(str[1]);
	cat = _strcat(cat, "=");
	cat = _strcat(cat, str[2]);
	index = find_env(*env, str[1]);
	if (index == -1)
	{
		add_end_node(env, cat);
	}
	else
	{
		holder = *env;
		while (j < index)
		{
			holder = holder->next;
			j++;
		}
		free(holder->var);
		holder->var = _strdup(cat);
	}
	free(cat);
	free_double_ptr(str);
	return (0);
}
