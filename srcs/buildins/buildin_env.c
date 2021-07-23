#include <libft.h>
#include <stdio.h>

int	buildin_env(char **tabl)
{
	while (*tabl)
	{
		if (ft_strchr(*tabl, '='))
			printf("%s\n", *tabl);
		tabl++;
	}
	return (0);
}
