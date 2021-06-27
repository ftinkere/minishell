#include "minishell.h"
#include "libft.h"
#include <stddef.h>

/*
** Раскрывает необходимые элементы лексем
*/

// TODO
t_vec_lex	*expand_env(t_vec_lex *lexes, char **env)
{
	return (lexes);
}

int	is_buildin(char *str)
{
	if (str == NULL)
		return (0);
	return (!ft_strncmp(str, "../", 3) || !ft_strcmp(str, "exit")
			|| !ft_strcmp(str, "env") || !ft_strcmp(str, "unset")
			|| !ft_strcmp(str, "export") || !ft_strcmp(str, "pwd")
			|| !ft_strcmp(str, "cd") || !ft_strcmp(str, "echo"));
}

int	is_comand(char *str)
{
	if (!ft_strncmp(str, "/", 1) || !ft_strncmp(str, "./", 2)
		|| is_buildin(str))
		return (0);
	return (1);
}

char	*expand_path_if_need(char *cmd)
{
	if (is_comand(cmd))
		return (get_path_by_comand(cmd));
	return (ft_strdup(cmd));
}