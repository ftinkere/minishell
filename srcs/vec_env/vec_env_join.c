#include <stdlib.h>
#include <minishell.h>
#include <libft.h>

t_vec_env	*vec_env_join(t_vec_env *env, char *str)
{
	char	*key;
	int		i;

	key = str_get_key(str);
	if (*key == '\0')
		return (env);
	key[ft_strlen(key) - 1] = '\0';
	i = env_keychr(env->arr, key);
	if (i == -1)
		vec_env_add(env, ft_strjoin(key, &str[ft_strlen(key) + 1]));
	else
		env->arr[i] = ft_strf1join(env->arr[i], &str[ft_strlen(key) + 2]);
	free(key);
	free(str);
	return (env);
}
