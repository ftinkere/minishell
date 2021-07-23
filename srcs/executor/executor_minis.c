#include <unistd.h>
#include <minishell.h>
#include <sys/signal.h>

void	exec_one(t_execve *exec, char **env)
{
	execve(exec->path, exec->argv, env);
}

char	*cmd_ex(t_pipeline *pipeline, int i)
{
	return (((t_execve **)pipeline->execves->arr)[i]->argv[0]);
}

pid_t	fork_and_signal_set(void)
{
	signal(SIGINT, sigint_proc_handler);
	signal(SIGQUIT, sigquit_proc_handler);
	return (fork());
}
