#include "libft.h"
#include "minishell.h"
#include <dirent.h>

static char	*get_path_by_comand_dir(char *cmd, char *dir_path)
{
	DIR				*dir;
	struct dirent	*ep;
	char			*name;

	dir = opendir(dir_path);
	if (dir != NULL)
	{
		ep = readdir(dir);
		while (ep != NULL)
		{
			if (!ft_strcmp(cmd, ep->d_name))
			{
				name = ft_strdup(ep->d_name);
				closedir(dir);
				return (ft_strf2join(dir_path, ft_strf2join("/", name)));
			}
			ep = readdir(dir);
		}
		closedir(dir);
	}
	return (NULL);
}

static char	*get_path_by_comand(char *cmd, t_vec_env *env)
{
	char	*path_env;
	char	**strs;
	int		i;
	char	*ret;

	path_env = env_get_value(env->arr, "PATH", 0);
	strs = ft_split(path_env, ':');
	i = 0;
	ret = NULL;
	while (strs[i] != NULL)
	{
		ret = get_path_by_comand_dir(cmd, strs[i]);
		if (ret != NULL)
			break ;
		i++;
	}
	free(path_env);
	free_split(strs);
	return (ret);
}

char	*expand_path(char *cmd, t_vec_env *env)
{
	if (is_comand(cmd))
		return (get_path_by_comand(cmd, env));
	return (ft_strdup(cmd));
}
