#include <minishell.h>
#include <libft.h>

t_vec_env	*vec_env_init(char **envp)
{
	t_vec_env	*ar;

	ar = (t_vec_env *)vec_init();
	if (envp == NULL)
		return (ar);
	while (*envp)
	{
		vec_env_add(ar, ft_strdup(*envp));
		envp++;
	}
	return (ar);
}
