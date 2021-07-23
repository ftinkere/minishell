#include <minishell.h>

t_vec	*vec_add(t_vec *vec, void *a)
{
	if (vec->size == vec->capacity - 1)
		vec_grow(vec);
	((void **)vec->arr)[vec->size++] = a;
	return (vec);
}
