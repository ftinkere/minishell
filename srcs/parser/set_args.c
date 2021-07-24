#include <minishell.h>
#include <libft.h>

void	set_args(t_pipeline *pipel, t_vec_lex *lex, int args_count, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j < args_count)
	{
		if (lex->arr[get_args(pipel, i * 2) + j].token == T_WORD)
		{
			get_execve(pipel, i)->argv[k] = \
					ft_strdup(lex->arr[get_args(pipel, i * 2) + j].str);
			k++;
		}
		j++;
	}
	((t_execve **)pipel->execves->arr)[i]->argv[k] = NULL;
}
