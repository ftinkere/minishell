#include <minishell.h>
#include <libft.h>

t_execve	*t_execve_init(void)
{
	t_execve	*ret;

	ret = ft_calloc(1, sizeof(t_execve));
	ret->fin = 0;
	ret->fout = 1;
	return (ret);
}
