#include <minishell.h>
#include <libft.h>

t_vec_lex	*vec_lex_grow(t_vec_lex *vec)
{
	void	*new_ptr;

	new_ptr = ft_calloc(vec->capacity * 2, sizeof(t_lex));
	ft_memcpy(new_ptr, vec->arr, vec->capacity * sizeof(t_lex));
	free(vec->arr);
	vec->arr = new_ptr;
	vec->capacity *= 2;
	return (vec);
}
