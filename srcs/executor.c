#include "minishell.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <printf.h>

/*
** Выполняет подготовленную команду
*/

void	executor(t_exec *exec, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(exec->path, exec->argv, exec->env);
		printf("Error\n");
		exit(0);
	}
	if (exec->wait)
		wait(&status);
}