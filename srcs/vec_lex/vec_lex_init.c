#include <minishell.h>
#include <libft.h>

t_vec_lex	*vec_lex_init(void)
{
	t_vec_lex	*vec;

	vec = malloc(sizeof(t_vec_lex));
	vec->capacity = 8;
	vec->size = 0;
	vec->arr = ft_calloc(vec->capacity, sizeof(t_lex));
	return (vec);
}
