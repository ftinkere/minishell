#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
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
		else
			vec_add(ret, tmp);
	}
	return (ret);
}

int	strs_to_in(t_vec *strs)
{
	int	tmpout;
	int	pipe_fd[2];

	pipe(pipe_fd);
	tmpout = dup(1);
//	dup2(1, pipe_fd[1]);
	dup2(pipe_fd[1], 1);
	print_strs(strs->arr);
	dup2(tmpout, 1);
	close(tmpout);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	ret_lessless_fd(char *end_str)
{
	t_vec	*readed;
	int ret;

	readed = vec_init();
	lessless(end_str, readed);
	ret = strs_to_in(readed);
	vec_free_all(readed);
	return (ret);
}
