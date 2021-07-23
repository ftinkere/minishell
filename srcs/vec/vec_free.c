#include <minishell.h>

void	vec_free(t_vec *vec)
{
	free(vec->arr);
	free(vec);
}
