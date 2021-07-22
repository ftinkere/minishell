#include <minishell.h>

static int	buildin_cd_home(t_vec_env *env)
{
	int	ret;

	if (ft_cmp_key(env->arr, "HOME") == -1)
		ret = chdir(getenv("HOME"));
	else
		ret = chdir(env->arr[ft_cmp_key(env->arr, "HOME")] + 5);
	return (ret);
}

int	ft_cd_buildin(t_execve *ex, t_vec_env *env)
{
	int	len_args;
	int	ret;

	ret = 0;
	len_args = 1;
	while (ex->argv[len_args])
		len_args++;
	if (len_args == 1)
		ret = buildin_cd_home(env);
	else if (len_args == 2)
		ret = chdir(ex->argv[1]);
	else if (len_args > 2)
	{
		printf("msh: cd: too many arguments\n");
		return (1);
	}
	if (ret < 0)
	{
		printf("msh: cd: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}
