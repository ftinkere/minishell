#include <stdlib.h>
#include <libft.h>
#include "vector.h"

t_vecl	*vecl_init(void)
{
	t_vecl	*vec;

	vec = malloc(sizeof(t_vecl));
	vec->capacity = 8;
	vec->size = 0;
	vec->arr = ft_calloc(vec->capacity, sizeof(t_lex));
	return (vec);
}

t_vecl	*vecl_grow(t_vecl *vec)
{
	void	*new_ptr;

	new_ptr = ft_calloc(vec->capacity * 2, sizeof(t_lex));
	ft_memcpy(new_ptr, vec->arr, vec->capacity * sizeof(t_lex));
	free(vec->arr);
	vec->arr = new_ptr;
	vec->capacity *= 2;
	return (vec);
}

t_vecl	*vecl_add(t_vecl *vec, t_lex lex)
{
	if (vec->size == vec->capacity)
		vecl_grow(vec);
	vec->arr[vec->size++] = lex;
}

void	vecl_free(t_vecl *vec)
{
	free(vec->arr);
	free(vec);
}
