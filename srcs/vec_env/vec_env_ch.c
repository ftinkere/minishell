#include <minishell.h>

t_vec_env	*vec_env_ch(t_vec_env *env, char *str)
{
	char	*key;

	key = str_get_key(str);
	vec_env_rem(env, key);
	free(key);
	vec_env_add(env, str);
	return (env);
}

