#include <minishell.h>

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	vec_int_free(pipeline->args);
	i = 0;
	while (i < (int)pipeline->execves->size)
		i++;
	free_execves(pipeline->execves);
	free(pipeline);
}
