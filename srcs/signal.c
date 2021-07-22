#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>

extern int g_last_code;

void	sigint_handler(__attribute__((unused)) int status)
{
	g_last_code = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_proc_hadndler(__attribute__((unused)) int status)
{
	printf("\n");
}

void	sigquit_proc_handler(__attribute__((unused)) int status)
{
	printf("Quit (core dumped)\n");
}
