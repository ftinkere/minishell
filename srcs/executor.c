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

void	init_executor(t_files *f, int *i, int *ret)
{
	f->tmpin = dup(0);
	f->tmpout = dup(1);
	*ret = 1;
	*i = 0;
}

void	init_cycle(t_pipeline *pipel, int i)
{

	dup2(get_execve(pipel, i)->fin, 0);
	close(get_execve(pipel, i)->fin);
	dup2(get_execve(pipel, i)->fout, 1);
	close(get_execve(pipel, i)->fout);
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

int	executor(t_pipeline *pipel, t_vec_env *env)
{
	pid_t	pid;
	int		i;
	int		ret;
	t_files	f;

	init_executor(&f, &i, &ret);
	while (i * 2 < (int)pipel->args->size)
	{
		init_cycle(pipel, i);
		if (get_execve(pipel, i)->path == NULL)
			printf("msh: comand not found: %s\n", cmd_ex(pipel, i));
		else if (is_buildin(get_execve(pipel, i)->path))
			ft_buildin(get_execve(pipel, i), env);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				exec_one(get_execve(pipel, i), env->arr);
				printf("msh: %s: %s\n", cmd_ex(pipel, i), strerror(errno));
				ret = -1;
				break ;
			}
		}
		i++;
	}
	waitpid(pid, NULL, 0);
	end_executor(pipel, &f);
	return (ret);
}
