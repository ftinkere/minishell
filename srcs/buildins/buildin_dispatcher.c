#include <minishell.h>
#include <libft.h>

int	buildin_dispath(t_execve *ex, t_vec_env *env, int *last_code, int is_pipe)
{
	if (!ft_strcmp(ex->path, "echo"))
		*last_code = buildin_echo(ex);
	else if (!ft_strcmp(ex->path, "env"))
		*last_code = buildin_env(env->arr);
	else if (!ft_strcmp(ex->path, "export"))
		*last_code = buildin_export(ex, env, is_pipe);
	else if (!ft_strcmp(ex->path, "unset") && is_pipe == 1)
		*last_code = buildin_unset(ex, env);
	else if (!ft_strcmp(ex->path, "pwd"))
		*last_code = buildin_pwd(ex);
	else if (!ft_strcmp(ex->path, "cd") && is_pipe == 1)
		*last_code = buildin_cd(ex, env);
	else if (!ft_strcmp(ex->path, "exit"))
		buildin_exit(ex);
	return (*last_code);
}
