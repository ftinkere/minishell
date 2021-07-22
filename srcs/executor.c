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

void	init_executor(t_files *f, int *i, int *ret, t_vec_int **pids)
{
	f->tmpin = dup(0);
	f->tmpout = dup(1);
	*ret = 1;
	*i = 0;
	*pids = vec_int_init();
}

void	init_cycle(t_pipeline *pipel, int i)
{

	dup2(get_execve(pipel, i)->fin, 0);
	close(get_execve(pipel, i)->fin);
	dup2(get_execve(pipel, i)->fout, 1);
	close(get_execve(pipel, i)->fout);
}

void	end_executor(t_pipeline *pipeline, t_files *f, int *last_code, t_vec_int *pids)
{
	int	i;

	i = 0;
	while (i < pids->size)
	{
		waitpid(((pid_t *)pids->arr)[i], last_code, 0);
		i++;
		*last_code = WEXITSTATUS(*last_code);
	}
	vec_int_free(pids);
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

int	executor(t_pipeline *pipel, t_vec_env *env, int *last_code)
{
	t_vec_int	*pids;
	pid_t		pid;
	int			i;
	int			ret;
	t_files		f;

	init_executor(&f, &i, &ret, &pids);
	while (i * 2 < (int)pipel->args->size)
	{
		init_cycle(pipel, i);
		if (get_execve(pipel, i)->path == NULL)
		{
			*last_code = 127;
			printf("msh: comand not found: %s\n", cmd_ex(pipel, i));
		}
		else if (is_buildin(get_execve(pipel, i)->path))
			ft_buildin(get_execve(pipel, i), env, last_code,
				(int)pipel->args->size / 2);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				exec_one(get_execve(pipel, i), env->arr);
				*last_code = errno;
				perror(cmd_ex(pipel, i));
//				printf("msh: %s: %s\n", cmd_ex(pipel, i), strerror(errno));
				ret = -1;
				break ;
			}
			else
				vec_int_add(pids, (int)pid);
		}
		i++;
	}
	end_executor(pipel, &f, last_code, pids);
	return (ret);
}
