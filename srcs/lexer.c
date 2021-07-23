#include "minishell.h"
#include "libft.h"

static enum e_token	get_token(char *str)
{
	if (!ft_strcmp(str, S_GREATE))
		return (T_GREATE);
	else if (!ft_strcmp(str, S_LESS))
		return (T_LESS);
	else if (!ft_strcmp(str, S_LESSLESS))
		return (T_LESSLESS);
	else if (!ft_strcmp(str, S_GREATEGREATE))
		return (T_GREATGREATE);
	else if (!ft_strcmp(str, S_PIPE))
		return (T_PIPE);
	else
		return (T_WORD);
}

static int	get_len(char *str)
{
	int	ret;
	int	quote;

	ret = 0;
	quote = 0;
	while (str[ret] && (!ft_strchr(" \t\n><;&|", str[ret]) || quote != 0))
	{
		if (str[ret] == '"' && quote == 0)
			quote = 1;
		else if ((str[ret] == '"' && str[ret - 1] != '\\' && quote == 1 ) || \
				(str[ret] == '\'' && quote == -1))
			quote = 0;
		else if (str[ret] == '\'' && quote == 0)
			quote = -1;
		ret++;
	}
	if (ret == 0 && (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2)))
		return (2);
	else if (ret == 0)
		return (1);
	return (ret);
}

static void	get_lex(t_vec_lex *vec, char *str, int *i)
{
	int		word_len;
	t_lex	lex;

	word_len = get_len(&str[*i]);
	lex.str = ft_substr(str, *i, word_len);
	lex.token = get_token(lex.str);
	vec_lex_add(vec, lex);
	*i += word_len;
	while (str[*i] && ft_strchr(" \t", str[*i]))
		(*i)++;
}

t_vec_lex	*lexer(char *str)
{
	t_vec_lex	*ret;
	int			i;

	ret = vec_lex_init();
	i = 0;
	while (ft_strchr(" \n\t", str[i]))
		i++;
	while (str[i] != '\0')
		get_lex(ret, str, &i);
	return (ret);
}
