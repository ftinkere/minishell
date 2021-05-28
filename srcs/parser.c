#include <stdio.h>
#include "minishell.h"
#include "libft.h"

/*
**
** Парсит набор лексем в выполняемую структуру
**
*/

int	count_args(t_vec_lex *lexes, int start)
{
	int	ret;

	ret = 0;
	if (lexes->size <= start || start < 0)
		return (0);
	while (ret + start < lexes->size && lexes->arr[ret + start].token == T_WORD)
		ret++;
	return (ret);
}

t_execve	*get_execve(t_pipeline *pipeline, int i)
{
	return (&((t_execve *)pipeline->execves->arr)[i]);
}

int	get_args(t_pipeline *pipeline, int i)
{
	return (((int *)pipeline->args->arr)[i]);
}

void	set_execves(t_pipeline *pipeline, t_vec_lex *lexes)
{
	int	args_count;
	int	i;
	int	j;

	i = 0;
	while (i * 2 < pipeline->args->size)
	{
		args_count = get_args(pipeline, i * 2 + 1);
		get_execve(pipeline, i)->path = \
			lexes->arr[get_args(pipeline, i * 2)].str;
		get_execve(pipeline, i)->argv = \
			ft_calloc(args_count + 1, sizeof(char *));
		j = 0;
		while (j < args_count) {
			get_execve(pipeline, i)->argv[j] = \
				lexes->arr[get_args(pipeline, i * 2) + j].str;
			j++;
		}
		((t_execve *)pipeline->execves->arr)[i].argv[j] = NULL;
		i++;
	}
}

int	count_pipes(t_vec_lex *lexes)
{
	int ret;
	int	i;

	ret = 1;
	i = 0;
	while (i < lexes->size)
	{
		if (lexes->arr[i].token == T_PIPE)
			ret++;
		i++;
	}
	return (ret);
}

t_pipeline	*parser(t_vec_lex *lexes, char **env)
{
	t_pipeline	*pipeline;
	int			i;
	int			pipe_count;
	int			arg;

	if (lexes->size < 1)
		return (NULL);
	pipeline = pipeline_init();
	pipeline->lexes = lexes;
	vec_add(pipeline->execves, ft_calloc(1, sizeof(t_execve)));

	// Зацикловать относительно количества команд в пайплайне
	// И вычислять начала и количества аргументов
	// Учесть начальные переменные среды в команде
	pipe_count = count_pipes(lexes);
	i = 0;
	arg = 0;
	while (i < pipe_count)
	{
		vec_int_add(pipeline->args, arg);
		vec_int_add(pipeline->args, count_args(lexes, arg));
		arg += count_args(lexes, arg) + 1;
		if (arg - 1 > lexes->size)
			printf("Error while pipe-parse, arg: %d, tokens: %lu\n", arg, lexes->size);
		i++;
	}
	set_execves(pipeline, lexes);

	pipeline->envp = env;

	if (lexes->arr[lexes->size - 1].token == T_AMP)
		pipeline->wait = 0;
	return (pipeline);
}