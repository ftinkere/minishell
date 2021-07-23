#include <minishell.h>

int	piper(t_pipeline *pipel, int *pipe_n, t_vec_lex *lex, int i)
{
	int		pipe_fd[2];

	if (check_err_redirect(lex, i))
		return (1);
	pipe(pipe_fd);
	if (get_execve(pipel, *pipe_n)->fin == 0)
		get_execve(pipel, *pipe_n)->fin = dup(0);
	if (get_execve(pipel, *pipe_n)->fout == 1)
		get_execve(pipel, *pipe_n)->fout = pipe_fd[1];
	else
		close(pipe_fd[1]);
	get_execve(pipel, *pipe_n + 1)->fin = pipe_fd[0];
	(*pipe_n)++;
	return (0);
}
