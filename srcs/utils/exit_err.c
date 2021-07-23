#include <sys/signal.h>
#include "minishell.h"

void	exit_err(enum e_err_type err)
{
	static const char	*str_err[] = {
		"Malloc could not allocate memory"
	};

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (err == ERR_MALLOC)
	{
		printf("msh: %s\n", str_err[ERR_MALLOC]);
		exit(128 + 12);
	}
}
