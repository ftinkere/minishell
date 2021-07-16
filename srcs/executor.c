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

void	init_executor(t_pipeline *pipeline, t_files *f, int *i, int *ret)
{
	lessless(pipeline->end_token, pipeline->readed_ll);

	f->tmpin = dup(0);
	f->tmpout = dup(1);
	if (pipeline->file_in)
		f->fdin = open(pipeline->file_in, O_RDONLY);
	else
		f->fdin = strs_to_in(pipeline->readed_ll->arr);
	vec_free_all(pipeline->readed_ll);
	*ret = 1;
	*i = 0;
}

void	init_cycle(t_pipeline *pipeline, t_files *f, int i)
{
	dup2(f->fdin, 0);
	close(f->fdin);
	if (i == pipeline->args->size / 2 - 1)
	{
		if (pipeline->file_out && pipeline->append_out)
			f->fdout = open(pipeline->file_out, MOD_APP, RIGHTS);
		else if (pipeline->file_out)
			f->fdout = open(pipeline->file_out, MOD, RIGHTS);
		else
			f->fdout = dup(f->tmpout);
	}
	else
	{
		pipe(f->fdpipe);
		f->fdout = f->fdpipe[1];
		f->fdin = f->fdpipe[0];
	}
	dup2(f->fdout, 1);
	close(f->fdout);
}

void	end_executor(t_pipeline *pipeline, t_files *f, int pid)
{
	dup2(f->tmpin, 0);
	dup2(f->tmpout, 1);
	close(f->tmpin);
	close(f->tmpout);
	free_pipeline(pipeline);
}

int	executor(t_pipeline *pipeline, t_vec_env *env)
{
	pid_t	pid;
	int		i;
	int		ret;
	t_files	f;

	init_executor(pipeline, &f, &i, &ret);
	while (i * 2 < (int)pipeline->args->size)
	{
		init_cycle(pipeline, &f, i);
		if (((t_execve **)pipeline->execves->arr)[i]->path == NULL)
			write(2, "Comand not found\n", 17);
		else if (is_buildin(((t_execve **)pipeline->execves->arr)[i]->path))
			ft_buildin(((t_execve **)pipeline->execves->arr)[i], env);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				exec_one(((t_execve **)pipeline->execves->arr)[i], env->arr);
				printf("Error, dont execed\n");
				ret = -1;
				break ;
			}
			else
				waitpid(pid, NULL, 0);
		}
		i++;
	}
	end_executor(pipeline, &f, pid);
	return (ret);
}
