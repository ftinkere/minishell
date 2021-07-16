#include "minishell.h"
#include "libft.h"

size_t	ft_tab_size(char **tabl)
{
	size_t	siz;

	siz = 0;
	while (*tabl)
	{
		siz = siz + strlen(*tabl);
		tabl++;
	}
	return (siz);
}

void	print_env(char **tabl)
{
	while (*tabl)
	{
		if (strchr(*tabl, '='))
			printf("%s\n", *tabl);
		tabl++;
	}
}

//char **ins_row(char **tabl, char *str)
//{
//    int i = 0;
//    char **new_tab;
//
//    new_tab = (char**)malloc(sizeof(char) * ft_tab_size(tabl));
//    while(*tabl)
//    {
//        new_tab[i] = strdup(*tabl);
//        i++;
//        tabl++;
//    }
//    new_tab[i] = (char*)malloc(sizeof(char) * strlen(str) + 1);
//    new_tab[i] = strdup(str);
//    i = 0;
//    /*while(tabl[i])
//    {
//        free(tabl[i]);
//        tabl[i] = NULL;
//        i++;
//    }*/
//    return (new_tab);
//}

//char **del_row(char **tabl, char *str)
//{
//    char **new_tab;
//    int i;
//    int j;
//
//    i = 0;
//    j = 0;
//    new_tab = (char**)malloc(sizeof(char) * (ft_tab_size(tabl)));
//    while(tabl[i])
//    {
//        if (!strncmp(str, tabl[i], strlen(str)) && strlen(str_key(tabl[i])) == strlen(str))
//        {
//            if (i == ft_count_rows_tab(tabl) - 1)
//                break;
//            i++;
//
//        }
//        new_tab[j] = strdup(tabl[i]);
//        i++;
//        j++;
//    }
//    i = 0;
//    /*while(tabl[i])
//    {
//        free(tabl[i]);
//        tabl[i] = NULL;
//        i++;
//    }*/
//    return (new_tab);
//}

int	ft_count_rows_tab(char **tabl)
{
	int	count;

	count = 0;
	while (*tabl)
	{
		count++;
		tabl++;
	}
	return (count);
}

int	*mass_env(char **tabl, int *mass, int i, int j)
{
	int	tmp;

	while (tabl[i])
	{
		j = 1;
		while (tabl[j])
		{
			if (tabl[mass[j]][0] < tabl[mass[j - 1]][0])
			{
				tmp = mass[j];
				mass[j] = mass[j - 1];
				mass[j - 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (mass);
}

void	ft_exp_str(char *str)
{
	int	i;

	i = 0;
	write(1, "declare -x ", 11);
	while (i < ft_strlen(str_key(str)) + 1)
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	ft_putchar_fd('"', 1);
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	ft_putchar_fd(34, 1);
	ft_putchar_fd('\n', 1);
}

// TODO: Сделать и для больше 50
void	print_export_env(char **tabl)
{
	int	i;
	int	mass[50];
	//int j = 1;
//	int	tmp;

	i = -1;
	while (++i < 50)
		mass[i] = i;
	i = 0;
	while (tabl[i])
	{
		if (tabl[i] != NULL)
			//printf("declare -x %s\n", tabl[(mass_env(tabl, mass, 0, 1))[i]]);
			ft_exp_str(tabl[(mass_env(tabl, mass, 0, 1))[i]]);
		i++;
	}
}

char	*str_key(char *str)
{
	int		i;
	char	*ret;
	int		j;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	ret = (char *) malloc(sizeof(char) * (i + 1));
	j = 0;
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

int	ft_cmp_key(char **tabl, char *key)
{
	int	i;

	i = 0;
	while (tabl[i])
	{
		if (!strncmp(tabl[i], key, strlen(key)) && tabl[i][strlen(key)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

//char  **ft_cpy_val(char **tabl, char *key)
//{
//    int i;
//    int j;
//
//    j = 0;
//
//    while(tabl[j])
//    {
//        i = 0;
//        if(!strncmp(tabl[j], str_key(key), strlen(str_key(key))))
//        {
//            while (tabl[j][i] && key[i])
//            {
//                if (tabl[j][i] == key[i])
//                    i++;
//                else
//                {
//                    tabl[j][i] = key[i];
//                    i++;
//                }
//            }
//            if(strlen(tabl[j]) > strlen(key))
//                tabl[j][i] = '\0';
//        }
//        j++;
//    }
//    return (tabl);
//}

//char        *ft_substr(char const *s, unsigned int start, size_t len)
//{
//        char        *sub_s;
//        size_t        i;
//
//        if (!s)
//                return (NULL);
//        if (start > strlen(s))
//                len = 0;
//        i = 0;
//        if (!(sub_s = (char*)malloc(sizeof(char) * (len + 1))))
//                return (NULL);
//        while (i < len)
//        {
//                sub_s[i] = s[start];
//                i++;
//                start++;
//        }
//        sub_s[i] = '\0';
//        return (sub_s);
//}
