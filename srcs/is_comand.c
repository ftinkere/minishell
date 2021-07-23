#include <libft.h>
#include <minishell.h>

int	is_comand(char *str)
{
	if (!ft_strncmp(str, "/", 1) || !ft_strncmp(str, "./", 2)
		|| !ft_strncmp(str, "../", 3) || is_buildin(str))
		return (0);
	return (1);
}
