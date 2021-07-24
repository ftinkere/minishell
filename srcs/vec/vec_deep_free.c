#include <minishell.h>

int	vec_deep_free(t_vec *vec)
{
	int	i;

	i = 0;
	while (i < (int)vec->size)
		free(((void **)vec->arr)[i++]);
	free(vec->arr);
	free(vec);
	return (1);
}
