#include "shell.h"

/**
 *stat_fun - Evaluates initial condition of arguments
 *@_str: Pointer of pointer to evaluate
 *@_fl: Flag to control pointer free
 *@_com: Command in the shell
 *@env: Environ variable
 *@c: Count the cicles
 *@av_0: First main argument
 *
 *Return: Integer 1 or 0
 */

int stat_fun(char **_str, int *_fl, char *_com, int c, char *av_0, char **env)
{
	struct stat  *bf;
	int no_path = 0;

	*_str = func_env(_com, env, &no_path);
	if (*_str != NULL)
		*_fl += 1;
	if (*_str == NULL)
	{
		bf = malloc(sizeof(struct stat));
		if (bf == NULL)
			return (1);
		if (stat(_com, bf) == 0 && S_ISDIR(bf->st_mode))
		{
			*_fl += 1;
			_printf("%s: %d: %s: Permission denied\n", av_0, c, _com);
			free(bf);
			return (1);
		}
		else if (stat(_com, bf) == 0 && S_ISREG(bf->st_mode))
		{
			*_str = _com;
			free(bf);
		}
		else
			free(bf);
	}
	return (no_path);
}
