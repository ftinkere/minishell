#include "minishell.h"
#include <stdio.h>
#include <dirent.h>
#include <readline/readline.h>

int	do_line(char *str, t_vec_env *env, int *last_code)
{
	t_vec_lex	*lexes;
	t_pipeline	*pipe;
	int			ret_redirect;
	int			ret;

	if (*str == '\0')
		return (0);
	lexes = lexer(str);
	pipe = parser(expand_env(lexes, env, *last_code), &ret_redirect, &ret, env);
	if (ret_redirect)
		return (ret_redirect);
	if (ret)
		return (ret);
	ret = executor(pipe, env, last_code);
	vecl_free(lexes);
	return (ret);
}

//int	main(void)
//{
//	int			last_code;
//	t_vec_env	*env;
//	t_vec_lex	*lex;
//
//	last_code = 0;
//	env = (t_vec_env *)vec_init();
//	do_line("echo $?", env, &last_code);
//	do_line("/bin/cat", env, &last_code);
//	do_line("echo $?", env, &last_code);
////	printf("%s\n", dollar(env->arr, "?", 10));
////	printf("%s\n", dollar(env->arr, "?", 0));
//	//	do_line("export END_TOKEN=EOF", env);
////	lex = expand_env(lexer("echo $AAA"), env);
////	print_lexes(lex);
////	printf("%s\n", dollar(env->arr, "AAA"));
////	do_line("cat << $END_TOKEN", env);
////	printf("%s\n", dollar(env->arr, "BBB"));
////	do_line("env", env);
////	do_line("echo $AAA", env);
//}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/select.h>
#include <sys/signal.h>

#define STDIN_FILENO 0

struct termios org_opts;

/** Select to check if stdin has pending input */
int pending_input(void) {
	struct timeval tv;
	fd_set fds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
	select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &fds);
}

void	sig_blanca(int sig)
{
	printf("SIGNAL! %d!\n", sig);
}

/** Input terminal mode; save old, setup new */
void setup_terminal(void) {
	struct termios new_opts;
	tcgetattr(STDIN_FILENO, &org_opts);
	memcpy(&new_opts, &org_opts, sizeof(new_opts));
	new_opts.c_cc[VEOF]  = 4;
	new_opts.c_cc[VINTR] = 3;
//	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ISIG | ICRNL);
	signal(SIGQUIT, sig_blanca);
	signal(SIGILL, sig_blanca);

	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
}

/** Shutdown terminal mode */
void reset_terminal(void) {
	tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
}

/** Return next input or -1 if none */
int next_input(void) {
	if (!pending_input())
		return -1;
	int rtn = fgetc(stdin);
	printf("Found: %d\n", rtn);
	return(rtn);
}

int main()
{
	setup_terminal();

	printf("%s\n", readline(""));
	printf("Press Q to quit...\n");
	for (;;) {
		int key = next_input();
		if (key != -1) {
			if ((key == 113) || (key == 81)) {
				printf("\nNormal exit\n");
				break;
			}
		}
	}

	reset_terminal();
	return 0;
}