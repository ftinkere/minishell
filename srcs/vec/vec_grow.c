#include <minishell.h>
#include <libft.h>

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
