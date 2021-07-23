#include <libft.h>
#include "minishell.h"

t_vec	*vec_int_grow(t_vec *vec)
{
	void	*new_ptr;

	new_ptr = ft_calloc(vec->capacity * 2, sizeof(int));
	ft_memcpy(new_ptr, vec->arr, vec->capacity * sizeof(int));
	free(vec->arr);
	vec->arr = new_ptr;
	vec->capacity *= 2;
	return (vec);
}
