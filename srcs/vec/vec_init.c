#include <minishell.h>
#include <libft.h>

t_vec	*vec_init(void)
{
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	vec->capacity = 8;
	vec->size = 0;
	vec->arr = ft_calloc(vec->capacity, sizeof(void *));
	return (vec);
}
