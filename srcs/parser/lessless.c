#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include "minishell.h"

static t_vec
	*lessless(char *end_str, t_vec *ret)
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
	lessless(end_str, readed);
	ret = strs_to_in(readed);
	vec_deep_free(readed);
	return (ret);
}
