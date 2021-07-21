#include "minishell.h"
#include "libft.h"
#include <stddef.h>

/*
** Раскрывает необходимые элементы лексем
*/

int 	len_btwn_char(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == c && i <= len)
			len = i;
		else if (str[i] == c && i > len)
			return (i - len - 1);
		i++;
	}
	return (0);
}

char *find_key(char *str)
{
	int 	i;
	char 	*key;

	i = 1;
	if (str[1] == '?')
		return (ft_strdup("?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	key = ft_substr(str, 1, (i - 1));
	return (key);
}

int 	count_char_quotes(char *str, int flag_quotes)
{
	int i;

	i = 0;
	if (flag_quotes == 1)
	{
		while (str[i] && str[i] != '$' && str[i] != '\\' && str[i] != '"')
			i++;
	}
	else if (flag_quotes == 0)
	{
		while (str[i] && str[i] != '\'' && str[i] != '$' && str[i] != '\\'
				&& str[i] != '"')
			i++;
	}
	else
	{
		while (str[i] && str[i] != '\'')
			i++;
	}
	return (i);
}

int move_count(char *str)
{
	if (str[0] == '\0')
		return (0);
	else if (str[0] == '"' || str[0] == '\'' || (str[0] == '\\' && str[1] == '\0'))
		return (1);
	else if (str[0] == '\\')
		return (2);
	else if (str[0] == '$')
		return (ft_strlen(find_key(str)) + 1);
	return (0);
}

char	*ret_str(char *str, t_vec_env *env, int last_code)
{
	char *ret_str;
	int i;
	int fl_quotes;
	int len;

	i = 0;
	fl_quotes = 0;
	ret_str = (char *)ft_calloc(1, 1);
	while (str[i])
	{
		len = count_char_quotes(&str[i], fl_quotes);
		ret_str = ft_strfjoin(ret_str, ft_substr(str, i, len));
		i += len;
		if (str[i] == '\'' && fl_quotes == 0)
			fl_quotes = -1;
		else if ((str[i] == '\'' && fl_quotes == -1)
				|| (str[i] == '"' && fl_quotes == 1))
			fl_quotes = 0;
		else if (str[i] == '"' && fl_quotes == 0)
			fl_quotes = 1;
		else if (str[i] == '$')
			ret_str = ft_strfjoin(ret_str,
					dollar(env->arr, find_key(str + i), last_code));
		//i += ft_strlen(find_key(str + i));
		else if (str[i] == '\\' && fl_quotes != -1 && str[i + 1])
			ret_str = ft_strfjoin(ret_str, ft_substr(str, i + 1, 1));
		i += move_count(str + i);
	}
		//обрабатываем одну строку "text $USER" => text user
		// вернуть новую замаллоченную строку
	return(ret_str);
}


t_vec_lex	*expand_env(t_vec_lex *lexes, t_vec_env *env, int last_code)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < lexes->size)
	{
		if	(lexes->arr[i].token == T_WORD)
		{
			tmp = lexes->arr[i].str;
			lexes->arr[i].str = ret_str(tmp, env, last_code);
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

int	is_buildin(char *str)
{
	if (str == NULL)
		return (0);
	return (!ft_strcmp(str, "exit") || !ft_strcmp(str, "env")
			|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "export")
			|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "cd")
			|| !ft_strcmp(str, "echo"));
}

int	is_comand(char *str)
{
	if (!ft_strncmp(str, "/", 1) || !ft_strncmp(str, "./", 2)
		|| !ft_strncmp(str, "../", 3) || is_buildin(str))
		return (0);
	return (1);
}

char	*expand_path_if_need(char *cmd, t_vec_env *env)
{
	if (is_comand(cmd))
		return (get_path_by_comand(cmd, env));
	return (ft_strdup(cmd));
}
