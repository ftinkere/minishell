#include <stdio.h>
#include "minishell.h"
#include "libft.h"
#include <stddef.h>

static void	in_out_fix(t_pipeline *pipel, int pipe_n)
{
	if (get_execve(pipel, 0)->fin == 0)
		get_execve(pipel, 0)->fin = dup(0);
	if (get_execve(pipel, pipe_n)->fout == 1)
		get_execve(pipel, pipe_n)->fout = dup(1);
}

static int	add_redirects(t_pipeline *pipel, t_vec_lex *lex)
{
	int	i;
	int	pipe_n;
	int	ret;

	ret = 0;
	pipe_n = 0;
	i = 0;
	while (i < (int)lex->size && ret == 0)
	{
		if (lex->arr[i].token == T_PIPE)
			piper(pipel, &pipe_n, lex, i);
		else if (lex->arr[i].token == T_LESS)
			ret = add_less(get_execve(pipel, pipe_n), lex, i);
		else if (lex->arr[i].token == T_LESSLESS)
			ret = add_lessless(get_execve(pipel, pipe_n), lex, i);
		else if (lex->arr[i].token == T_GREATE)
			ret = add_greate(get_execve(pipel, pipe_n), lex, i);
		else if (lex->arr[i].token == T_GREATGREATE)
			ret = add_greategreate(get_execve(pipel, pipe_n), lex, i);
		i++;
	}
	in_out_fix(pipel, pipe_n);
	return (ret);
}

static int
	set_execves(t_pipeline *pipel, t_vec_lex *lex, t_vec_env *env)
{
	int	args_count;
	int	i;
	int	j;

	i = 0;
	while (i * 2 < (int)pipel->args->size)
	{
		args_count = get_args(pipel, i * 2 + 1);
		if (args_count == 0)
			return (1);
		get_execve(pipel, i)->path = \
			expand_path(lex->arr[get_args(pipel, i * 2)].str, env);
		get_execve(pipel, i)->argv = \
			ft_calloc(args_count + 1, sizeof(char *));
		set_args(pipel, lex, args_count, i);
		i++;
	}
	return (0);
}

static t_pipeline
	*check_start(t_pipeline *pipel, t_vec_lex *lexes, int *ret_parse)
{
	printf("msh: syntax error: next to unexpected token «%s»\n",
		lexes->arr[1].str);
	*ret_parse = 1;
	return (pipel);
}

t_pipeline
	*parser(t_vec_lex *lexes, int *ret, t_vec_env *env)
{
	t_pipeline	*pipeline;
	int			i;
	int			pipe_count;
	int			arg;

	if (lexes->size < 1)
		return (NULL);
	pipeline = pipeline_init();
	pipeline->lexes = lexes;
	pipe_count = count_pipes(lexes);
	if (lexes->arr[0].token != T_WORD)
		return (check_start(pipeline, lexes, ret));
	i = 0;
	arg = 0;
	while (i < pipe_count)
	{
		vec_int_add(pipeline->args, arg);
		vec_int_add(pipeline->args, count_args(lexes, arg));
		vec_add(pipeline->execves, t_execve_init());
		arg += count_args(lexes, arg) + 1;
		i++;
	}
	*ret = add_redirects(pipeline, lexes);
	*ret = *ret || set_execves(pipeline, lexes, env);
	return (pipeline);
}
