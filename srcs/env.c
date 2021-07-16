#include "minishell.h"
#include "libft.h"

t_vec_env	*env_buildin(char **envp)
{
	t_vec_env	*ar;

	ar = (t_vec_env *)vec_init();
	while (*envp)
	{
		vec_env_add(ar, ft_strdup(*envp));
		envp++;
	}
	return (ar);
}

char	*dollar(char **tabl, char *key)
{
	char	*ret_str;
	int		flag;

	flag = 0;
	while (*tabl)
	{
		if (!strncmp(*tabl, key, strlen(key)) && *tabl[strlen(key)] == '=')
		{
			ret_str = ft_substr(*tabl, strlen(key) + 1,
					strlen(*tabl) - strlen(key));
			flag = 1;
		}
		tabl++;
	}
	if (flag == 0)
		return (NULL);
	else
		return (ret_str);
}

int	ft_buildin(t_execve *ar, t_vec_env *env_tab)
{
	if (!ft_strcmp(ar->path, "echo"))
		ft_echo(ar);
	else if (!ft_strcmp(ar->path, "env"))
		print_env(env_tab->arr);
	else if (!ft_strcmp(ar->path, "export"))
		ft_export_env(ar, env_tab);
	else if (!ft_strcmp(ar->path, "unset"))
		ft_unset_env(ar, env_tab);
	else if (!ft_strcmp(ar->path, "pwd"))
		ft_pwd_buildin(ar);
	else if (!ft_strcmp(ar->path, "cd"))
		ft_cd_buildin(ar);
	else if (!ft_strcmp(ar->path, "exit"))
	{
		printf("exit\n");
		if (ar->argv[1] == NULL)
			exit(0);
		else
			exit(ft_atoi(ar->argv[1]));
	}
	return (1);
}
