#include <libft.h>
#include "minishell.h"

t_vec	*vec_int_add(t_vec *vec, int a)
{
	if (vec->size == vec->capacity - 1)
		vec_int_grow(vec);
	((int *)vec->arr)[vec->size++] = a;
	return (vec);
}
