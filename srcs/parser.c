#include <stdio.h>
#include "minishell.h"
#include "libft.h"
#include <stddef.h>

/*
**
** Парсит набор лексем в выполняемую структуру
**
*/

int	count_args(t_vec_lex *lex, int start)
{
	int	ret;

	ret = 0;
	if ((int)lex->size <= start || start < 0)
		return (0);
	while (ret + start < (int)lex->size
		&& lex->arr[ret + start].token != T_PIPE)
		ret++;
	return (ret);
}

t_execve	*get_execve(t_pipeline *pipeline, int i)
{
	return (((t_execve **)pipeline->execves->arr)[i]);
}

int	get_args(t_pipeline *pipeline, int i)
{
	return (((int *)pipeline->args->arr)[i]);
}

int	check_err_redirect(t_vec_lex *lex, int i)
{
	if (lex->arr[i].token == T_WORD)
		return (0);
	if (i == lex->size - 1)
	{
		printf("msh: syntax error: unexpected EOF\n");
		return (1);
	}
	else if (lex->arr[i + 1].token != T_WORD)
	{
		printf("msh: syntax error: next to unexpected token «%s»\n",
			   lex->arr[i + 1].str);
		return (1);
	}
	return (0);
}

int	set_execves(t_pipeline *pipel, t_vec_lex *lex, t_vec_env *env)
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
			expand_path_if_need(lex->arr[get_args(pipel, i * 2)].str, env);
		get_execve(pipel, i)->argv = \
			ft_calloc(args_count + 1, sizeof(char *));
		j = 0;
		while (j < args_count)
		{
			if (lex->arr[get_args(pipel, i * 2) + j].token == T_WORD)
				get_execve(pipel, i)->argv[j] = \
					ft_strdup(lex->arr[get_args(pipel, i * 2) + j].str);
			j++;
		}
		((t_execve **)pipel->execves->arr)[i]->argv[j] = NULL;
		i++;
	}
	return (0);
}

int	count_pipes(t_vec_lex *lexes)
{
	int	ret;
	int	i;

	ret = 1;
	i = 0;
	while (i < (int)lexes->size)
	{
		if (lexes->arr[i].token == T_PIPE)
			ret++;
		i++;
	}
	return (ret);
}

int	add_less(t_execve *ex, t_vec_lex *lex, int i)
{
	if (check_err_redirect(lex, i))
		return (1);
	if (ex->fin != 0)
		close(ex->fin);
	ex->fin = open(lex->arr[i + 1].str, O_RDONLY);
	return (0);
}

int	add_lessless(t_execve *ex, t_vec_lex *lex, int i)
{
	if (check_err_redirect(lex, i))
		return (1);
	if (ex->fin != 0)
		close(ex->fin);
	ex->fin = ret_lessless_fd(lex->arr[i + 1].str);
	return (0);
}

int	add_greate(t_execve *ex, t_vec_lex *lex, int i)
{
	if (check_err_redirect(lex, i))
		return (1);
	if (ex->fout != 1)
		close(ex->fout);
	ex->fout = open(lex->arr[i + 1].str, MOD, RIGHTS);
	return (0);
}

int	add_greategreate(t_execve *ex, t_vec_lex *lex, int i)
{
	if (check_err_redirect(lex, i))
		return (1);
	if (ex->fout != 1)
		close(ex->fout);
	ex->fout = open(lex->arr[i + 1].str, MOD_APP, RIGHTS);
	return (0);
}

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

int	add_redirects(t_pipeline *pipel, t_vec_lex *lex)
{
	int	i;
	int	pipe_n;
	int	ret;

	ret = 0;
	pipe_n = 0;
	i = 0;
	while (i < (int)lex->size && ret == 0)
	{
		if (lex->arr[i].token == T_WORD)
			;
		else if (lex->arr[i].token == T_PIPE)
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
	if (get_execve(pipel, 0)->fin == 0)
		get_execve(pipel, 0)->fin = dup(0);
	if (get_execve(pipel, pipe_n)->fout == 1)
		get_execve(pipel, pipe_n)->fout = dup(1);
	return (ret);
}

t_execve	*new_t_execve(void)
{
	t_execve	*ret;

	ret = ft_calloc(1, sizeof(t_execve));
//	ret->fin = dup(0);
//	ret->fout = dup(1);
	ret->fin = 0;
	ret->fout = 1;
	return (ret);
}

t_pipeline	*parser(t_vec_lex *lexes, int *ret_redirect, int *ret_parse,
		t_vec_env *env)
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
	i = 0;
	arg = 0;
	while (i < pipe_count)
	{
		vec_int_add(pipeline->args, arg);
		vec_int_add(pipeline->args, count_args(lexes, arg));
		vec_add(pipeline->execves, new_t_execve());
		arg += count_args(lexes, arg) + 1;
		i++;
	}
	*ret_redirect = add_redirects(pipeline, lexes);
	*ret_parse = set_execves(pipeline, lexes, env);
	return (pipeline);
}
