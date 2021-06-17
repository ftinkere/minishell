#include <minishell.h>
#include <libft.h>

t_pipeline	*pipeline_init()
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	pipeline->lexes = NULL;
	pipeline->args = vec_int_init();
	pipeline->execves = vec_init();
	pipeline->wait = 1;
	pipeline->append_out = 0;
	pipeline->envp = vec_init();
	return (pipeline);
}