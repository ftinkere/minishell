#include <minishell.h>

int	count_args(t_vec_lex *lex, int start)
{
	int	ret;

	ret = 0;
	if ((int)lex->size <= start || start < 0)
		return (0);
	while (ret + start < (int)lex->size
		&& lex->arr[ret + start].token != T_PIPE)
		ret++;
	return (ret);
}
