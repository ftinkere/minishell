#include "../include/minishell.h"
#include "libft.h"

int	ft_echo(t_execve *ex)
{
	int	i;

	i = 1;
	if (!ft_strcmp(ex->argv[1], "-n"))
		i++;
	while (ex->argv[i])
	{
		printf("%s ", ex->argv[i]);
		i++;
	}
	if (ft_strcmp(ex->argv[1], "-n"))
		printf("\n");
	return (1);
}

int	ft_export_env(t_execve *ex, t_vec_env *env)
{
	int	i;

	i = 1;
	if (!ex->argv[1])
		print_export_env(env->arr);
	else
	{
		while (ex->argv[i])
		{
			if (ft_strchr(ex->argv[i], '+') && ft_strchr(ex->argv[i], '='))
				vec_env_plus(env, ft_strdup(ex->argv[i]));
			else
				vec_env_ch(env, ft_strdup(ex->argv[i]));
			i++;
		}
	}
	return (1);
}

int	ft_unset_env(t_execve *ex, t_vec_env *env)
{
	int	i;

	i = 1;
	while (ex->argv[i])
	{
		vec_env_rem(env, ex->argv[i]);
		i++;
	}
	return (1);
}

void	ft_cd_buildin(t_execve *ex,  int *last_code, t_vec_env *env)
{
	int	i;

	i = 1;
	if (!ex->argv[1])
		chdir(env->arr[ft_cmp_key(env->arr, "HOME")] + 5);
	else
	{
		while (ex->argv[i])
		{
			i++;
		}
		if (i > 2)
			printf("msh: cd: too many arguments\n");
		else if ((chdir(ex->argv[1])) == -1)
			printf("msh: cd: %s\n", strerror(errno));
		else
			return;
	}
	*last_code = 1;
}

void	ft_pwd_buildin(t_execve *ex)
{
	char	*dir;

	if (!strcmp(ex->path, "pwd"))
	{
		dir = getcwd(NULL, 0);
		printf("%s\n", dir);
		free(dir);
	}
}

char	*ft_strdup_prob(char *src)
{
	size_t	i;
	size_t	len;
	char	*str;

	len = 0;
	while (src[len] != ' ' && src[len])
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
