#include <stdlib.h>
#include <../libft/libft.h>
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

t_vec_env *vec_env_add(t_vec_env *vec, char *a)
{
	if (vec->size == vec->capacity - 1)
		vec_grow((t_vec *)vec);
	((char **)vec->arr)[vec->size++] = a;
	return (vec);
}

t_vec_env *vec_env_rem(t_vec_env *vec, char *key)
{
	int i;

	if (vec->size == 0)
		return (vec);
	i = ft_cmp_key(vec->arr, key);
	if (i < 0)
		return (vec);
	free(vec->arr[i]);
	ft_memmove(&vec->arr[i], &vec->arr[i + 1], vec->size - i - 1); // при size == 0 ошибка
	vec->arr[vec->size] = NULL;
	vec->size--;
	return (vec);
}

t_vec_env *vec_env_ch(t_vec_env *env, char *str)
{
	int i;
	char *key;

	key = str_key(str);
	i = ft_cmp_key(env->arr, key);
	free(key);

	if (i < 0)
		vec_env_add(env, str);
	else
	{
		free(env->arr[i]);
		env->arr[i] = str;
	}
	return (env);
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
	while (i < (int)vec->size)
		free(((void **)vec->arr)[i++]);
	free(vec->arr);
	free(vec);
}
