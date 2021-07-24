#include "minishell.h"
#include "libft.h"

static int	get_len_to_semicolon(const char *str)
{
	int	ret;
	int	quote;

	ret = 0;
	quote = 0;
	if (*str == '\0')
		return (-1);
	while (str[ret] && (str[ret] != ';' || quote != 0))
	{
		if (str[ret] == '"' && quote == 0)
			quote = 1;
		else if ((str[ret] == '"' && str[ret - 1] != '\\' && quote == 1)
			|| (str[ret] == '\'' && quote == -1))
			quote = 0;
		else if (str[ret] == '\'' && quote == 0)
			quote = -1;
		ret++;
	}
	return (ret);
}

static int	get_block(t_vec *vec, char *str, int *i)
{
	int		len_to_semicolon;
	char	*block;

	len_to_semicolon = get_len_to_semicolon(&str[*i]);
	if (len_to_semicolon == -1)
		return (-1);
	block = ft_substr(str, *i, len_to_semicolon);
	vec_add(vec, block);
	*i += len_to_semicolon;
	if (str[*i] == ';')
		*i += 1;
	while (str[*i] && ft_strchr(" \t", str[*i]))
		(*i)++;
	return (1);
}

t_vec	*split_semicolon(char *str)
{
	t_vec	*ret;
	int		i;

	ret = vec_init();
	i = 0;
	while (str[i])
	{
		if (get_block(ret, str, &i) == -1)
			break ;
	}
	return (ret);
}
