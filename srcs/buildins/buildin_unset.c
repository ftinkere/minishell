#include <minishell.h>

int	buildin_unset(t_execve *ex, t_vec_env *env)
{
	int	i;

	i = 1;
	while (ex->argv[i])
	{
		vec_env_rem(env, ex->argv[i]);
		i++;
	}
	return (0);
}
