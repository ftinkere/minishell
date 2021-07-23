#include <libft.h>
#include <stdlib.h>
#include <minishell.h>

t_vec_env	*vec_env_rem(t_vec_env *env, char *key)
{
	int	i;

	if (env->size == 0)
		return (env);
	i = env_keychr(env->arr, key);
	if (i < 0)
		return (env);
	free(env->arr[i]);
	ft_memmove(&env->arr[i], &env->arr[i + 1], env->size - i);
	env->arr[env->size - 1] = NULL;
	env->size--;
	return (env);
}
