#include "minishell.h"
#include "libft.h"

t_vec_env *env_buildin(char **envp)
{
    t_vec_env *ar;
    //int i;

    //i = 0;
    ar = (t_vec_env*)vec_init();
    while(*envp)
    {
		vec_env_add(ar, ft_strdup(*envp));
		//ar->arr[i] = strdup(*envp);
        //i++;
        envp++;
    }
   return (ar);
}

char *dollar(char **tabl, char *key)
{
    char *ret_str;

    if (!key || !*key)
    	return (ft_strdup(""));
    while(*tabl)
    {
        if(!ft_strncmp(*tabl, key, ft_strlen(key)) && (*tabl)[ft_strlen(key)] == '=')
        {
            ret_str = ft_substr(*tabl, ft_strlen(key) + 1,
								ft_strlen(*tabl) - ft_strlen(key));
			return(ret_str);
        }
        tabl++;
    }
    return (ft_strdup(""));
}

int ft_buildin(t_execve *ar, t_vec_env *env_tab)
{
	//char **env_tab;
    //if (!(env_tab = env_buildin(env)))  //
	//	return (-1);						//
    //if (!strcmp(ar->path, "export"))
   //     print_export_env(ar->env_tab);
    if (!ft_strcmp(ar->path, "echo"))
        ft_echo(ar);
    else if (!ft_strcmp(ar->path, "env"))
		print_env(env_tab->arr);
    else if (!ft_strcmp(ar->path, "export"))
		ft_export_env(ar, env_tab);
    else if (!ft_strcmp(ar->path, "unset"))
		ft_unset_env(ar, env_tab);
    else if (!ft_strcmp(ar->path, "pwd"))
        ft_pwd_buildin(ar);
    else if (!ft_strcmp(ar->path, "cd"))
        ft_cd_buildin(ar);
    else if(!ft_strcmp(ar->path, "exit"))
        {
            printf("exit\n");
            if(ar->argv[1] == NULL)
            	exit(0);
            else
            	exit(ft_atoi(ar->argv[1]));
        }
    return (1);
}
