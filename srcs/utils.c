#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int	free_ret(void *fred, int ret)
{
	free(fred);
	return (ret);
}

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
	vec_free_all(execves);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	vec_int_free(pipeline->args);
	i = 0;
	while (i < pipeline->execves->size)
	{
//		if (get_execve(pipeline, i)->fin > 2)
//			close(get_execve(pipeline, i)->fin);
//		if (get_execve(pipeline, i)->fout > 2)
//			close(get_execve(pipeline, i)->fout);
		i++;
	}
	free_execves(pipeline->execves);
//	if (pipeline->file_in)
//		free(pipeline->file_in);
//	if (pipeline->file_out)
//		free(pipeline->file_out);
	free(pipeline);
}
