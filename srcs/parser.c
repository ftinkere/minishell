#include <minishell.h>
#include <libft.h>

/*
**
** Парсит набор лексем в выполняемую структуру
**
*/

int	count_args(t_vecl *lexes, int start)
{
	int	ret;

	ret = 0;
	if (lexes->size <= start || start < 0)
		return (0);
	while (ret + start < lexes->size && lexes->arr[ret + start].token == T_WORD)
		ret++;
	return (ret);
}

void	get_argv(t_exec *exec, t_vecl *lexes, int start)
{
	int	args_count;
	int	i;

	args_count = count_args(lexes, start);
	exec->argv = ft_calloc(args_count + 1, sizeof(char *));
	i = 0;
	while (i < args_count)
	{
		exec->argv[i] = lexes->arr[start + i].str;
		i++;
	}
	exec->argv[i] = 0;
}

t_exec	*parser(t_vecl *lexes, char **env)
{
	t_exec	*exec;

	if (lexes->size < 1)
		return (NULL);
	exec = ft_calloc(1, sizeof(t_exec));
	exec->size = 1;
	exec->args_index_pairs = ft_calloc(2 * exec->size, sizeof(int));
	exec->lexes = lexes;
	exec->path = lexes->arr[0].str;
	get_argv(exec, lexes, 0);
	exec->argv[0] = exec->path;
	exec->env = env;
	exec->wait = 1;
	if (lexes->arr[lexes->size - 1].token == T_AMP)
		exec->wait = 0;
	return (exec);
}