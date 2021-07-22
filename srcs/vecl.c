#include <stdlib.h>
#include <libft.h>
#include "minishell.h"

/*
**
** Обработка вектора лексем
**
*/

t_vec_lex	*vecl_init(void)
{
	t_vec_lex	*vec;

	vec = malloc(sizeof(t_vec_lex));
	vec->capacity = 8;
	vec->size = 0;
	vec->arr = ft_calloc(vec->capacity, sizeof(t_lex));
	return (vec);
}

t_vec_lex	*vecl_grow(t_vec_lex *vec)
{
	void	*new_ptr;

	new_ptr = ft_calloc(vec->capacity * 2, sizeof(t_lex));
	ft_memcpy(new_ptr, vec->arr, vec->capacity * sizeof(t_lex));
	free(vec->arr);
	vec->arr = new_ptr;
	vec->capacity *= 2;
	return (vec);
}

t_vec_lex	*vecl_add(t_vec_lex *vec, t_lex lex)
{
	if (vec->size == vec->capacity - 1)
		vecl_grow(vec);
	vec->arr[vec->size++] = lex;
	return(vec); //
}

void	vecl_free(t_vec_lex *vec)
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
