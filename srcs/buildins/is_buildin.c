#include <libft.h>

int	is_buildin(char *str)
{
	if (str == NULL)
		return (0);
	return (!ft_strcmp(str, "exit") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "echo"));
}
