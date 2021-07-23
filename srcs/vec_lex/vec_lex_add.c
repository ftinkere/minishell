#include <minishell.h>

t_vec_lex	*vec_lex_add(t_vec_lex *vec, t_lex lex)
{
	if (vec->size == vec->capacity - 1)
		vec_lex_grow(vec);
	vec->arr[vec->size++] = lex;
	return (vec);
}
