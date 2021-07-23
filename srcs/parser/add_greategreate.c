#include <minishell.h>

int	add_greategreate(t_execve *ex, t_vec_lex *lex, int i)
{
	if (check_err_redirect(lex, i))
		return (1);
	if (ex->fout != 1)
		close(ex->fout);
	ex->fout = open(lex->arr[i + 1].str,
			(O_CREAT | O_WRONLY | O_APPEND),
			(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
	return (0);
}
