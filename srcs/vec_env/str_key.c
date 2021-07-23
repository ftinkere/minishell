#include <malloc.h>

char	*str_key(const char *str)
{
	int		key_len;
	char	*ret;
	int		i;

	key_len = 0;
	while (str[key_len] != '\0' && str[key_len] != '=')
		key_len++;
	ret = (char *)malloc(sizeof(char) * (key_len + 1));
	i = 0;
	while (i < key_len)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
