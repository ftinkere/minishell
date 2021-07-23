#include <minishell.h>

int	get_args(t_pipeline *pipeline, int i)
{
	return (((int *)pipeline->args->arr)[i]);
}
