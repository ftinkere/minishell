#include "minishell.h"
#include "libft.h"

static int	n_flag_processing(t_execve *ex, int *n_flag)
{
	int	i;
	int	j;

	*n_flag = 0;
	i = 1;
	while (ex->argv[i] != NULL && !ft_strncmp("-", ex->argv[i], 1))
	{
		j = 1;
		while (ex->argv[i][j] == 'n')
			j++;
		if (ex->argv[i][j] != '\0' || ex->argv[i][1] == '\0')
			break ;
		*n_flag = 1;
		i++;
	}
	return (i);
}

int	buildin_echo(t_execve *ex)
{
	int	i;
	int	n_flag;

	i = n_flag_processing(ex, &n_flag);
	while (ex->argv[i])
	{
		printf("%s", ex->argv[i]);
		if (ex->argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 0 || ex->argv[1] == NULL)
		printf("\n");
	return (0);
}
