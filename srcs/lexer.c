#include "minishell.h"
#include "libft.h"

/*
**
** Обработка строки в набор лексем
**
*/

enum e_token	get_token(char *str)
{
	if (!ft_strcmp(str, S_GREATE))
		return (T_GREATE);
	else if (!ft_strcmp(str, S_LESS))
		return (T_LESS);
	else if (!ft_strcmp(str, S_GREATEGREATE))
		return (T_GREATGREATE);
	else if (!ft_strcmp(str, S_GREATEAMP))
		return (T_GREATEAMP);
	else if (!ft_strcmp(str, S_GREATEGREATEAMP))
		return (T_GREATGREATEAMP);
	else if (!ft_strcmp(str, S_PIPE))
		return (T_PIPE);
	else if (!ft_strcmp(str, S_AMP))
		return (T_AMP);
	else if (!ft_strcmp(str, S_SEMICOLON))
		return (T_SEMICOLON);
	else
		return (T_WORD);
}

int	get_len(char *str)
{
	int		ret;
	char	quote;

	ret = 0;
	quote = 0;
	while (str[ret] && (!ft_strchr(" \t\n", str[ret]) || quote != 0))
	{
		if (str[ret] == '"' && quote == 0)
			quote = 1;
		else if (str[ret] == '"' && str[ret - 1] != '\\' && quote == 1)
			quote = 0;
		else if (str[ret] == '\'' && quote == 0)
			quote = -1;
		else if (str[ret] == '\'' && quote == -1)
			quote = 0;
		ret++;
	}
	return (ret);
}

void	get_lex(t_vecl *vec, char *str, int *i)
{
	int		word_len;
	t_lex	lex;

	word_len = get_len(&str[*i]);
	lex.str = ft_substr(str, *i, word_len);
	lex.token = get_token(lex.str);
	vecl_add(vec, lex);
	*i += word_len;
	while (str[*i] && ft_strchr(" \t", str[*i]))
		(*i)++;
}

t_vecl	*lexer(char *str)
{
	t_vecl	*ret;
	int		i;

	ret = vecl_init();
	i = 0;
	while (ft_strchr(" \n\t", str[i]))
		i++;
	while (str[i] != '\0')
		get_lex(ret, str, &i);
	return (ret);
}
