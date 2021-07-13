#include "minishell.h"
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

/*
** Выполняет подготовленную команду
*/

void	exec_one(t_execve *exec, char **env)
{
	execve(exec->path, exec->argv, env);
}

int	executor(t_pipeline *pipeline, t_vec_env *env)
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

	if (pipeline->file_in)
		fdin = open(pipeline->file_in, O_RDONLY);
	else
		fdin = dup(tmpin);
	ret = 1;
	i = 0;
	while (i * 2 < (int)pipeline->args->size)
	{
		dup2(fdin, 0);
		close(fdin);
		if (i == pipeline->args->size / 2 - 1)
		{
			if (pipeline->file_out && pipeline->append_out)
				fdout = open(pipeline->file_out, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
			else if (pipeline->file_out)
				fdout = open(pipeline->file_out, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
			else
				fdout = dup(tmpout);
		}
		else
		{
			pipe(fdpipe); // Посмотреть нет ли утечек дескрипторов // кажется нет
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);

		if (is_buildin(((t_execve **)pipeline->execves->arr)[i]->path))
		{
			ft_buildin(((t_execve **)pipeline->execves->arr)[i], env);
			//break ;
		}
		else
		{
			pid = fork();
			if (pid == 0) {
				exec_one(((t_execve **)pipeline->execves->arr)[i], env->arr);
				printf("Error, dont execed\n");
				ret = -1;
				break ;
			}
			else if (pipeline->wait)
				waitpid(pid, NULL, 0);
		}
		i++;
	}
	if (pipeline->wait)
		waitpid(pid, NULL, 0);
//		wait(NULL);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
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