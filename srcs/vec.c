#include <stdlib.h>
#include <libft.h>
#include "minishell.h"

/*
**
** Обработка вектора указателей
**
*/

t_vec	*vec_init(void)
{
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	vec->capacity = 8;
	vec->size = 0;
	vec->arr = ft_calloc(vec->capacity, sizeof(void *));
	return (vec);
}

t_vec	*vec_grow(t_vec *vec)
{
	void	*new_ptr;

	new_ptr = ft_calloc(vec->capacity * 2, sizeof(void *));
	ft_memcpy(new_ptr, vec->arr, vec->capacity * sizeof(void *));
	free(vec->arr);
	vec->arr = new_ptr;
	vec->capacity *= 2;
	return (vec);
}

t_vec	*vec_add(t_vec *vec, void *a)
{
	if (vec->size == vec->capacity - 1)
		vec_grow(vec);
	((void **)vec->arr)[vec->size++] = a;
	return (vec);
}

void	vec_free(t_vec *vec)
{
	free(vec->arr);
	free(vec);
}

void	vec_free_all(t_vec *vec)
{
	int	i;

	i = 0;
	while (i < vec->size)
		free(((void **)vec->arr)[i++]);
	free(vec->arr);
	free(vec);
}
