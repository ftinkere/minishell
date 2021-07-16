#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signal.h>
#include "minishell.h"

t_vec	*lessless(char *end_str, t_vec *ret)
{
	char	*tmp;
	int		cont;

	if (end_str == NULL)
		return (ret);
	cont = 1;
	while (cont)
	{
		tmp = readline("> ");
		if (tmp == NULL || !strcmp(end_str, tmp))
			cont = 0;
		if (tmp != NULL && (end_str == (void *)1 || !strcmp(end_str, tmp)))
			free(tmp);
		else if (tmp != NULL)
			vec_add(ret, tmp);
	}
	return (ret);
}

int	strs_to_in(char **strs)
{
	int	tmpout;
	int	pipe_fd[2];

	if (strs == NULL)
		return (dup(0));
	pipe(pipe_fd);
	tmpout = dup(1);
	dup2(1, pipe_fd[1]);
	print_strs(strs);
	dup2(tmpout, 1);
	close(tmpout);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
