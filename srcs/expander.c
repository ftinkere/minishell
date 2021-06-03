#include "minishell.h"
#include "libft.h"

/*
** Раскрывает необходимые элементы лексем
*/

// TODO
t_vec_lex	*expand_env(t_vec_lex *lexes, char **env)
{
	return (lexes);
}

int	is_comand(char *str)
{
	if (!ft_strncmp(str, "/", 1) || !ft_strncmp(str, "./", 2)
		|| !ft_strncmp(str, "../", 3))
		return (0);
	return (1);
}

char	*expand_path_if_need(char *cmd)
{
	if (is_comand(cmd))
		return (get_path_by_comand(cmd));
	return (ft_strdup(cmd));
}