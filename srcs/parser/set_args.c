#include <minishell.h>
#include <libft.h>

static int	check_arg(t_vec_lex *lex, int arg)
{
	if (arg < 0)
		return (1);
	if (lex->arr[arg].token == T_WORD || lex->arr[arg].token == T_PIPE)
		return (1);
	return (0);
}

void	set_args(t_pipeline *pipel, t_vec_lex *lex, int args_count, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j < args_count)
	{
		if (lex->arr[get_args(pipel, i * 2) + j].token == T_WORD
			&& check_arg(lex, get_args(pipel, i * 2) + j - 1))
		{
			get_execve(pipel, i)->argv[k] = \
					ft_strdup(lex->arr[get_args(pipel, i * 2) + j].str);
			k++;
		}
		j++;
	}
	((t_execve **)pipel->execves->arr)[i]->argv[k] = NULL;
}
