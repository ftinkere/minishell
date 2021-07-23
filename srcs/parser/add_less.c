#include <minishell.h>

int	add_less(t_execve *ex, t_vec_lex *lex, int i)
{
	if (check_err_redirect(lex, i))
		return (1);
	if (ex->fin != 0)
		close(ex->fin);
	ex->fin = open(lex->arr[i + 1].str, O_RDONLY);
	return (0);
}
