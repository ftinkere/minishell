#include "minishell.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

extern int	g_last_code;

static void
	init_executor(t_files *f, int *i, int *ret, t_vec_int **pids)
{
	f->tmpin = dup(0);
	f->tmpout = dup(1);
	*ret = 1;
	*i = 0;
	*pids = vec_int_init();
	signal(SIGINT, SIG_IGN);
}

static void
	init_cycle(t_pipeline *pipel, int i)
{
	dup2(get_execve(pipel, i)->fin, 0);
	close(get_execve(pipel, i)->fin);
	dup2(get_execve(pipel, i)->fout, 1);
	close(get_execve(pipel, i)->fout);
}

static void
	end_executor(t_pipeline *pipeline, t_files *f, int *code, t_vec_int *pids)
{
	int	i;

	i = 0;
	while (i < (int)pids->size)
	{
		if (((pid_t *)pids->arr)[i] < 0)
			printf("Error while fork\n");
		else
			waitpid(((pid_t *)pids->arr)[i], code, 0);
		i++;
		if (WCOREDUMP(*code))
			*code = 131;
		else if (WIFSIGNALED(*code))
			*code = 128 + WTERMSIG(*code);
		else
			*code = WEXITSTATUS(*code);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	vec_int_free(pids);
	dup2(f->tmpin, 0);
	dup2(f->tmpout, 1);
	close(f->tmpin);
	close(f->tmpout);
	free_pipeline(pipeline);
}

static int
	executor_cycle(int i, t_pipeline *pipel, t_vec_env *env, t_vec_int *pids)
{
	pid_t	pid;

	init_cycle(pipel, i);
	if (get_execve(pipel, i)->path == NULL)
	{
		g_last_code = 127;
		printf("msh: comand not found: %s\n", cmd_ex(pipel, i));
	}
	else if (is_buildin(get_execve(pipel, i)->path))
		buildin_dispath(get_execve(pipel, i), env, &g_last_code,
			(int) pipel->args->size / 2);
	else
	{
		pid = fork_and_signal_set();
		if (pid == 0)
		{
			exec_one(get_execve(pipel, i), env->arr);
			g_last_code = 126;
			perror(cmd_ex(pipel, i));
			return (-1);
		}
		else
			vec_int_add(pids, (int)pid);
	}
	return (1);
}

int	executor(t_pipeline *pipel, t_vec_env *env, int *last_code)
{
	t_vec_int	*pids;
	int			i;
	int			ret;
	t_files		f;

	init_executor(&f, &i, &ret, &pids);
	while (i * 2 < (int)pipel->args->size)
	{
		ret = executor_cycle(i, pipel, env, pids);
		if (ret < 0)
			break ;
		i++;
	}
	end_executor(pipel, &f, last_code, pids);
	return (ret);
}
