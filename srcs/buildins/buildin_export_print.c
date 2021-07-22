#include <minishell.h>
#include <libft.h>

static int	*mass_env(char **tabl, int *mass)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
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

static void	ft_exp_str(char *str)
{
	char	*key;

	key = str_key(str);
	printf("declare -x %s=\"%s\"\n", key, &str[ft_strlen(key) + 1]);
	free(key);
}

void	print_export_env(char **tabl)
{
	int	i;
	int	*mass;

	i = 0;
	mass = (int *)malloc(sizeof(int) * ft_count_rows_tab(tabl));
	if (mass == NULL)
		exit_err(ERR_MALLOC);
	while (i < ft_count_rows_tab(tabl))
	{
		mass[i] = i;
		i++;
	}
	mass_env(tabl, mass);
	i = 0;
	while (tabl[i])
	{
		if (tabl[i] != NULL)
			ft_exp_str(tabl[mass[i]]);
		i++;
	}
	free(mass);
}
