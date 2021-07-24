#include <minishell.h>

int	check_err_redirect(t_vec_lex *lex, int i)
{
	if (lex->arr[i].token == T_WORD)
		return (0);
	if (i == (int)lex->size - 1)
	{
		printf("msh: syntax error: unexpected EOF\n");
		return (1);
	}
	else if (lex->arr[i + 1].token != T_WORD)
	{
		printf("msh: syntax error: next to unexpected token «%s»\n",
			lex->arr[i + 1].str);
		return (1);
	}
	return (0);
}
