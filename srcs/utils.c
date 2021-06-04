#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	free_execves(t_vec *execves)
{
	int	i;
	int	j;

	i = 0;
	while (i < execves->size)
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
	vec_free_all(execves);
}

void	free_pipeline(t_pipeline *pipeline)
{
	vec_int_free(pipeline->args);
	free_execves(pipeline->execves);
	vec_free_all(pipeline->envp);
	if (pipeline->file_in)
		free(pipeline->file_in);
	if (pipeline->file_out)
		free(pipeline->file_out);
	if (pipeline->file_err)
		free(pipeline->file_err);
	free(pipeline);
}
