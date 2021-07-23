#include <minishell.h>

t_vec_env	*vec_env_add(t_vec_env *env, char *str)
{
	if (env->size == env->capacity - 1)
		vec_grow((t_vec *)env);
	env->arr[env->size++] = str;
	return (env);
}
