#include "minishell.h"
#include "libft.h"
#include <stddef.h>
#include <sys/signal.h>

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

char	*dollar(char **tabl, char *key, int	last_code)
{
	if (key == NULL || *key == '\0')
		return (ft_strdup(""));
	if (!ft_strcmp(key, "?"))
		return (ft_itoa(last_code));
	while (*tabl)
	{
		if (!ft_strncmp(*tabl, key, ft_strlen(key))
				&& (*tabl)[ft_strlen(key)] == '=')
			return (ft_substr(*tabl, ft_strlen(key) + 1,
							ft_strlen(*tabl) - ft_strlen(key)));
		tabl++;
	}
	return (ft_strdup(""));
}

void ft_exit_builin(t_execve *ex)
{
	int	i;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	printf("exit\n");
	if (ex->argv[1] == NULL)
		exit(0);
	i = 0;
	while ((*ex->argv)[i] && ft_isdigit((*ex->argv)[i]))
		i++;
	if ((*ex->argv)[i] != '\0')
	{
		printf("msh: exit: %s: numeric argument required\n", ex->argv[1]);
		exit(2);
	}
	else
		exit(ft_atoi(ex->argv[1]) % 256);
}

int	ft_buildin(t_execve *ar, t_vec_env *env_tab, int *last_code, int num_cmds)
{
	if (!ft_strcmp(ar->path, "echo"))
		*last_code = buildin_echo(ar);
	else if (!ft_strcmp(ar->path, "env"))
		*last_code = print_env(env_tab->arr);
	else if (!ft_strcmp(ar->path, "export"))
		*last_code = buildin_export(ar, env_tab, num_cmds);
	else if (!ft_strcmp(ar->path, "unset") && num_cmds == 1)
		*last_code = buildin_unset(ar, env_tab);
	else if (!ft_strcmp(ar->path, "pwd"))
		*last_code = ft_pwd_buildin(ar);
	else if (!ft_strcmp(ar->path, "cd") && num_cmds == 1)
		*last_code = ft_cd_buildin(ar, env_tab);
	else if (!ft_strcmp(ar->path, "exit"))
		ft_exit_builin(ar);
	return (1);
}
