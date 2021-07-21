#include "../include/minishell.h"
#include "libft.h"

int	ft_echo(t_execve *ex)
{
	int	i;
	int	j;
	int	n_flag;

	n_flag = 0;
	i = 1;
	while (ex->argv[i] != NULL && !ft_strncmp("-", ex->argv[i], 1))
	{
		j = 1;
		while (ex->argv[i][j] != '\0' && ex->argv[i][j] == 'n')
			j++;
		if (ex->argv[i][j] != '\0' || ex->argv[i][1] == '\0')
			break ;
		n_flag = 1;
		i++;
	}
	while (ex->argv[i])
	{
		printf("%s", ex->argv[i]);
		if (ex->argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 0 || ex->argv[1] == NULL)
		printf("\n");
	return (1);
}

int	check_arg_export(char *str)
{
	int i;

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
				if (!check_arg_export(ex->argv[i]))
				{
					if (ft_strchr(ex->argv[i], '+')
							&& ft_strchr(ex->argv[i], '='))
						vec_env_plus(env, ft_strdup(ex->argv[i]));
					else
						vec_env_ch(env, ft_strdup(ex->argv[i]));
				}
				else
				{
					printf("msh: export: '%s': not a valid identifier\n",
						   ex->argv[i]);
					return (1);
				}
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
	int	len_args;
	int	ret;

	ret = 0;
	len_args = 1;
	while (ex->argv[len_args])
		len_args++;
	if (len_args == 1)
	{
		if (ft_cmp_key(env->arr, "HOME") == -1)
			ret = chdir(getenv("HOME"));
		else
			ret = chdir(env->arr[ft_cmp_key(env->arr, "HOME")] + 5);
	}
	else if (len_args == 2)
		ret = chdir(ex->argv[1]);
	else if (len_args > 2)
	{
		printf("msh: cd: too many arguments\n");
		*last_code = 1;
	}
	if (ret < 0)
		printf("msh: cd: %s\n", strerror(errno));
	*last_code = 0;
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

//char	*ft_strdup_prob(char *src)
//{
//	size_t	i;
//	size_t	len;
//	char	*str;
//
//	len = 0;
//	while (src[len] != ' ' && src[len])
//		len++;
//	str = (char *)malloc(sizeof(char) * (len + 1));
//	if (!str)
//		return (NULL);
//	i = 0;
//	while (i < len)
//	{
//		str[i] = src[i];
//		i++;
//	}
//	str[i] = '\0';
//	return (str);
//}
