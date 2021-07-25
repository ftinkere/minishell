#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/signal.h>
#include "minishell.h"

extern int	g_last_code;
int			g_signal_buf;

void	sig_lessless(int status)
{
	if (status == SIGINT)
	{
		g_signal_buf = 1;
		g_last_code = 130;
		rl_replace_line("", 0);
		rl_redisplay();
		write(0, "\0", 1);
	}
}

static t_vec
	*lessless(char *end_str, t_vec *ret)
{
	char	*tmp;
	int		cont;

	if (end_str == NULL)
		return (ret);
	g_signal_buf = 0;
	signal(SIGINT, sig_lessless);
	cont = 1;
	while (cont)
	{
		tmp = readline("> ");
		if (tmp == NULL && g_signal_buf == 0)
		{
			printf("msh: warning: here-document delimited by "\
			"end-of-file (wanted `%s`)\n", end_str);
		}
		if (tmp == NULL || !strcmp(end_str, tmp) || g_signal_buf == 1)
			cont = 0;
		else
			vec_add(ret, tmp);
	}
	signal(SIGINT, sigint_handler);
	return (ret);
}

static int
	strs_to_in(t_vec *strs)
{
	int	tmpout;
	int	pipe_fd[2];

	pipe(pipe_fd);
	tmpout = dup(1);
	dup2(pipe_fd[1], 1);
	print_strs((char **)strs->arr);
	dup2(tmpout, 1);
	close(tmpout);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	read_lessless__ret_fd(char *end_str)
{
	t_vec	*readed;
	int		ret;

	readed = vec_init();
	ret = 0;
	lessless(end_str, readed);
	if (g_signal_buf == 0)
		ret = strs_to_in(readed);
	vec_deep_free(readed);
	return (ret);
}
