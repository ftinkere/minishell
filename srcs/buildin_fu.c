#include "../include/minishell.h"
#include "libft.h"

int	ft_echo(t_execve *ex)
{
	int i;

	i = 1;
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
	int i;

	i = 1;
	if (ex->argv[1] == NULL)
		print_export_env(env->arr);
	else
	{
		while (ex->argv[i])
		{
			vec_env_ch(env, ft_strdup(ex->argv[i]));
			i++;
		}
	}
	return (1);
}

int	ft_unset_env(t_execve *ex, t_vec_env *env)
{
	int i;

	i = 1;
	while (ex->argv[i])
	{
		vec_env_rem(env, ex->argv[i]);
		i++;
	}
	return (1);
}

void	ft_cd_buildin(t_execve *ex)
{
	int i;

	i = 1;
	while (ex->argv[i])
	{
		if ((chdir(ex->argv[i])) == -1)
			printf("msh: cd: %s\n", strerror(errno));
		i++;
	}
}

void	ft_pwd_buildin(t_execve *ex)
{
	char dir[100] = {0};

	if (!strcmp(ex->path, "pwd"))
	{
		getcwd(dir, 100);
		printf("%s\n", dir);
	}

}

char	*ft_strdup_prob(char *src)
{
	size_t i;
	size_t len;
	char *str;

	len = 0;
	while (src[len] != ' ' && src[len])
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
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
