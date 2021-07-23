#include <libft.h>

int	env_keychr(char **tabl, char *key)
{
	int	i;

	i = 0;
	while (tabl[i])
	{
		if (!ft_strncmp(tabl[i], key, ft_strlen(key))
			&& tabl[i][ft_strlen(key)] == '=')
			return (i);
		i++;
	}
	return (-1);
}
