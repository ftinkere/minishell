#include <stdio.h>
#include <readline/readline.h>

extern int	g_last_code;

void	sigint_handler(int status)
{
	(void)status;
	g_last_code = 130;
	printf("\b\b\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_proc_handler(int status)
{
	(void)status;
	printf("\n");
}

void	sigquit_proc_handler(int status)
{
	(void)status;
	printf("Quit (core dumped)\n");
}
