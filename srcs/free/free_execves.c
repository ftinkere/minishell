#include <minishell.h>

void	free_execves(t_vec *execves)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)execves->size)
	{
		free(((t_execve **)execves->arr)[i]->path);
		j = 0;
		while (((t_execve **)execves->arr)[i]->argv[j])
		{
			free(((t_execve **)execves->arr)[i]->argv[j]);
			j++;
		}
		free(((t_execve **)execves->arr)[i]->argv);
		i++;
	}
	vec_deep_free(execves);
}
