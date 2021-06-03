#include "libft.h"
#include "minishell.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

char	*get_path_by_comand_dir(char *cmd, char *dir_path)
{
	DIR				*dir;
	struct dirent	*ep;
	char			*tmp;

	dir = opendir(dir_path);
	if (dir != NULL)
	{
		ep = readdir(dir);
		while (ep != NULL)
		{
			if (!ft_strcmp(cmd, ep->d_name))
			{
				tmp = ft_strjoin("/", ep->d_name);
				closedir(dir);
				return (ft_strjoin(dir_path, tmp));
			}
			ep = readdir(dir);
		}
		closedir(dir);
	}
	return (NULL);
}

char	*get_path_by_comand(char *cmd)
{
	char	*path_env;
	char	**strs;
	int		i;
	char	*ret;

	path_env = getenv("PATH");
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
	free_split(strs);
	return (ret);
}
