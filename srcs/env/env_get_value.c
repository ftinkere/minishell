#include "minishell.h"
#include "libft.h"

char	*env_get_value(char **tabl, char *key, int	last_code)
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
