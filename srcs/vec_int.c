#include <stdlib.h>
#include <libft.h>
#include "minishell.h"

t_vec	*vec_int_init(void)
{
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	vec->capacity = 8;
	vec->size = 0;
	vec->arr = ft_calloc(vec->capacity, sizeof(int));
	return (vec);
}

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

t_vec	*vec_int_add(t_vec *vec, int a)
{
	if (vec->size == vec->capacity - 1)
		vec_int_grow(vec);
	((int *)vec->arr)[vec->size++] = a;
	return (vec);
}

void	vec_int_free(t_vec *vec)
{
	vec_free(vec);
}