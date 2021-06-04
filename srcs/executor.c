#include "minishell.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

/*
** Выполняет подготовленную команду
*/

void	exec_one(t_execve *exec, char **env)
{
	execve(exec->path, exec->argv, env);
}

int	executor(t_pipeline *pipeline, char **env)
{
	pid_t	pid;
	int		i;
	int		ret;
	// to struct:
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;
	int		fdpipe[2];

	tmpin = dup(0);
	tmpout = dup(1);

	// file_in вместо того:
	fdin = dup(tmpin);

	ret = 1;
	i = 0;
	while (i * 2 < pipeline->args->size)
	{
		dup2(fdin, 0);
		close(fdin);
		if (i == pipeline->args->size / 2 - 1)
		{
			// Есть ли file_out, иначе
			fdout = dup(tmpout);
		}
		else
		{
			pipe(fdpipe); // Посмотреть нет ли утечек дескрипторов
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);

		if (is_buildin(((t_execve **)pipeline->execves->arr)[i]->path))
		{
//			free_pipeline(pipeline);
			ret = 0;
			break ;
		}
		else
		{
			pid = fork();
			if (pid == 0) {
				exec_one(((t_execve **)pipeline->execves->arr)[i], env);
				printf("Error, dont execed\n");
				ret = -1;
				break ;
			}
		}
		i++;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	if (pipeline->wait)
		wait(NULL);
	free_pipeline(pipeline);
	return (ret);
}

//void	executor(t_pipeline *pipeline, char **env)
//{
//	pid_t	pid;
//	int		status;
//	int		i;
//
//	i = 0;
//	while (i * 2 < pipeline->args->size)
//	{
//		pid = fork();
//		if (pid == 0) {
//			exec_one(&((t_execve *) pipeline->execves->arr)[i], env);
//			printf("Error, pid: %d\n", pid);
//			exit(0);
//		}
//		if (pipeline->wait)
//			wait(&status);
//		i++;
//	}
//}