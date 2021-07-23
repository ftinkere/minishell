#include "minishell.h"

int	buildin_pwd(t_execve *ex)
{
	char	*dir;

	if (!strcmp(ex->path, "pwd"))
	{
		dir = getcwd(NULL, 0);
		printf("%s\n", dir);
		free(dir);
	}
	return (0);
}
