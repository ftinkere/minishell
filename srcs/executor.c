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

void	end_executor(t_pipeline *pipeline, t_files *f)
{
	dup2(f->tmpin, 0);
	dup2(f->tmpout, 1);
	close(f->tmpin);
	close(f->tmpout);
	free_pipeline(pipeline);
}

char	*cmd_ex(t_pipeline *pipeline, int i)
{
	return (((t_execve **)pipeline->execves->arr)[i]->argv[0]);
}

// TODO: Починить `cat`
int	executor(t_pipeline *pl, t_vec_env *env)
{
	pid_t	pid;
	int		i;
	int		ret;
	t_files	f;

	init_executor(pl, &f, &i, &ret);
	while (i * 2 < (int)pl->args->size)
	{
		init_cycle(pl, &f, i);
		if (get_execve(pl, i)->path == NULL)
			printf("msh: comand not found: %s\n", cmd_ex(pl, i));
		else if (is_buildin(get_execve(pl, i)->path))
			ft_buildin(get_execve(pl, i), env);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				exec_one(get_execve(pl, i), env->arr);
				printf("msh: %s: %s\n", cmd_ex(pl, i), strerror(errno));
				ret = -1;
				break ;
			}
			else
				waitpid(pid, NULL, 0);
		}
		i++;
	}
	end_executor(pl, &f);
	return (ret);
}
