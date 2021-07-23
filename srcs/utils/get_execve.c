#include <minishell.h>

t_execve	*get_execve(t_pipeline *pipeline, int i)
{
	return (((t_execve **)pipeline->execves->arr)[i]);
}
