#include "../include/minishell.h"
#include "libft.h"

int    ft_echo(t_execve *ex)
{
    int i;
    int j;
    char *key;
    char *ret_str;
    int	n_flag;
    
    i = 1;
    while (ex->argv[i])
	{
		printf("%s ", ex->argv[i]);
		i++;
	}
//    if (!strcmp(ex->path, "echo")) //
//    { //
//            while(str[i])
//            {
//                if (str[i] == ' ' || str[i] == '"' || str[i] == 39)
//                    i++;
//                else if (str[i] == '-' && str[i + 1] == 'n')
//                    i += 2;
//                else
//                {
//                    if (!strncmp(str, "$", 1) && strcmp(str, "$?"))
//                    {
//                        j = 0;
//                        key = strchr(str, '$') + 1;
//                        if((ret_str = dollar(ex->env_tab, key)) == NULL)
//                            write(1, "\n", 1);
//                        else
//                            write(1, ret_str, strlen(ret_str));
//                            write(1, " ", 1);
//                        //break;
//                    }
//                    else if (!strcmp(str, "$?"))
//                        {
//                            printf("%d", errno);
//                            break ;
//                        }
//                    else
//                    {
//                    printf ("%c", str[i]);
//                    i++;
//                    }
//                }
//            }
//    }//
		if(strcmp(ex->argv[1], "-n"))
            printf("\n");
    return (1);
}

int    ft_export_env(t_execve *ex, t_vec_env *env_tab)
{
    int i;

    i = 1;
    if (ex->argv[1] == NULL)
		print_export_env(env_tab->arr);
    else
	{
    	while(ex->argv[i])
    	{
//			if (!ft_cmp_key(env_tab, str_key(ex->argv[i]))) // замаенить весь блок на vec_env_ch
//				env_tab = ins_row(env_tab, ex->argv[i]);
//			else
//				env_tab = ft_cpy_val(env_tab, ex->argv[i]);
			vec_env_ch(env_tab, ft_strdup(ex->argv[i]));
			i++;
		}
	}
    
    return (1);
}

int    ft_unset_env(t_execve *arg, t_vec_env *env_tab)
{
	int i;

	i = 1;
    while (arg->argv[i])
    {
    	vec_env_rem(env_tab, arg->argv[i]);
		//env_tab = del_row(env_tab, arg->argv[i]);
		i++;
	}
    return (1);
}  

void    ft_cd_buildin(t_execve  *ex)
{
	int i;

	i = 1;
    while (ex->argv[i])
        {
            if((chdir(ex->argv[i])) == -1)
            printf("msh: cd: %s\n", strerror(errno));
            i++;
        }
}

void    ft_pwd_buildin(t_execve *ex)
{
    char dir[100] = {0};

    if (!strcmp(ex->path, "pwd"))
    {
        getcwd(dir, 100);
        printf ("%s\n", dir);
    }

}

char        *ft_strdup_prob(char *src)
{
        size_t        i;
        size_t        len;
        char        *str;

        len = 0;
        while (src[len] != ' ' && src[len])
                len++;
        if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
                return (NULL);
        i = 0;
        while (i < len)
        {
                str[i] = src[i];
                i++;
        }
        str[i] = '\0';
        return (str);
}