#include <minishell.h>

int	add_lessless(t_execve *ex, t_vec_lex *lex, int i)
{
	int	tmp;

	if (check_err_redirect(lex, i))
		return (1);
	tmp = read_lessless__ret_fd(lex->arr[i + 1].str);
	if (tmp != 0 && ex->fin != 0)
		close(ex->fin);
	if (tmp != 0)
		ex->fin = tmp;
	else
		return (1);
	return (0);
}
