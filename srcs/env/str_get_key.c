#include <libft.h>

//char	*str_get_key(const char *str)
//{
//	int		key_len;
//	char	*key;
//
//	key_len = 0;
//	while (str[key_len] != '\0' && str[key_len] != '=')
//		key_len++;
//	key = ft_substr(str, 0, key_len);
//	return (key);
//}

char	*str_get_key(const char *str)
{
	int		i;
	char	*key;

	i = 1;
	if (*str == '\0')
		return (ft_strdup(""));
	if (str[1] == '?')
		return (ft_strdup("?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 1)
		return (ft_strdup(""));
	key = ft_substr(str, 1, (i - 1));
	return (key);
}
