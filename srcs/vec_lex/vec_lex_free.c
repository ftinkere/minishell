#include "minishell.h"

void	vec_lex_free(t_vec_lex *vec)
{
	int	i;

	i = 0;
	while (i < (int)vec->size)
	{
		free(vec->arr[i].str);
		i++;
	}
	free(vec->arr);
	free(vec);
}
