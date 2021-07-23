#include <libft.h>
#include <minishell.h>

static int	check_arg_export(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i + 1])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			i++;
		else if ((!ft_isalnum(str[i]) && str[i] != '_'))
			return (1);
		i++;
	}
	return (0);
}

static int	export_arg(t_execve *ex, t_vec_env *env, int i)
{
	char	*plus;

	if (!check_arg_export(ex->argv[i]))
	{
		plus = ft_strchr(ex->argv[i], '+');
		if (plus != NULL && plus[1] == '=')
			vec_env_join(env, ft_strdup(ex->argv[i]));
		else
			vec_env_ch(env, ft_strdup(ex->argv[i]));
	}
	else
	{
		printf("msh: export: '%s': not a valid identifier\n", ex->argv[i]);
		return (0);
	}
	return (1);
}

int	buildin_export(t_execve *ex, t_vec_env *env, int num_cmds)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (ex->argv[1] == NULL)
		print_export_env(env->arr);
	else if (num_cmds == 1)
	{
		while (ex->argv[i])
		{
			if (!export_arg(ex, env, i))
				ret = 1;
			i++;
		}
	}
	return (ret);
}
