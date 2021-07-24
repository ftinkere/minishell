#include "minishell.h"
#include "libft.h"

static int	count_char_quotes(char *str, int flag_quotes)
{
	int	i;

	i = 0;
	if (flag_quotes == 1)
	{
		while (str[i] && !(str[i] == '\\' && (str[i + 1] == '\\'
					|| str[i + 1] == '"' || str[i + 1] == '$')) && str[i] != '"'
			&& (str[i] != '$' || (!ft_isalnum(str[i + 1]) && str[i + 1] != '_'
					&& str[i + 1] != '?')))
			i++;
	}
	else if (flag_quotes == 0)
	{
		while (str[i] && str[i] != '\'' && str[i] != '\\' && str[i] != '"'
			&& (str[i] != '$' || (!ft_isalnum(str[i + 1])
					&& str[i + 1] != '_')) && str[i + 1] != '?')
			i++;
	}
	else
	{
		while (str[i] && str[i] != '\'')
			i++;
	}
	return (i);
}

static int	move_count(char *str)
{
	char	*key;

	key = str_get_key(str);
	if (str[0] == '\0')
		return (free_ret(key, 0));
	else if (str[0] == '"' || str[0] == '\'' || (str[0] == '\\'
			&& str[1] == '\0'))
		return (free_ret(key, 1));
	else if (str[0] == '\\')
		return (free_ret(key, 2));
	else if (str[0] == '$' && (ft_isalnum(str[1]) || str[1] == '_'
			|| str[1] == '?'))
		return (free_ret(key, (int)ft_strlen(key) + 1));
	free(key);
	return (0);
}

static int	quotes(char *str, int i, int *fl_quotes)
{
	if (str[i] == '\'' && *fl_quotes == 0)
		*fl_quotes = -1;
	else if ((str[i] == '\'' && *fl_quotes == -1)
		|| (str[i] == '"' && *fl_quotes == 1))
		*fl_quotes = 0;
	else if (str[i] == '"' && *fl_quotes == 0)
		*fl_quotes = 1;
	else
		return (0);
	return (1);
}

static char	*expand_str(char *str, t_vec_env *env, int code)
{
	char	*key;
	char	*ret_str;
	int		i;
	int		fl_quotes;
	int		len;

	i = 0;
	fl_quotes = 0;
	ret_str = (char *)ft_calloc(1, 1);
	while (str[i])
	{
		len = count_char_quotes(&str[i], fl_quotes);
		ret_str = ft_strfjoin(ret_str, ft_substr(str, i, len));
		i += len;
		if (!quotes(str, i, &fl_quotes) && str[i] == '$')
		{
			key = str_get_key(&str[i]);
			ret_str = ft_strfjoin(ret_str, env_get_value(env->arr, key, code));
			free(key);
		}
		else if (str[i] == '\\' && fl_quotes != -1 && str[i + 1])
			ret_str = ft_strfjoin(ret_str, ft_substr(str, i + 1, 1));
		i += move_count(str + i);
	}
	return (ret_str);
}

t_vec_lex	*expand_env(t_vec_lex *lexes, t_vec_env *env, int last_code)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < (int)lexes->size)
	{
		if (lexes->arr[i].token == T_WORD)
		{
			tmp = lexes->arr[i].str;
			lexes->arr[i].str = expand_str(tmp, env, last_code);
			free(tmp);
		}
		if (lexes->arr[i].str[0] == '\0')
		{
			free(lexes->arr[i].str);
			ft_memmove(&lexes->arr[i], &lexes->arr[i + 1],
				(lexes->size - i) * sizeof (t_lex));
			lexes->size--;
		}
		else
			i++;
	}
	return (lexes);
}
