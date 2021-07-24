#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/signal.h>
#include <minishell.h>

void	buildin_exit(t_execve *ex)
{
	int	i;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	printf("exit\n");
	if (ex->argv[1] == NULL)
		exit(0);
	i = 0;
	while ((*ex->argv)[i] && ft_isdigit((*ex->argv)[i]))
		i++;
	if ((*ex->argv)[i] == '\0')
	{
		printf("msh: exit: %s: numeric argument required\n", ex->argv[1]);
		exit(1);
	}
	else
		exit(ft_atoi(ex->argv[1]) % 256);
}
