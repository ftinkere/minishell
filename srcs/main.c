#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/signal.h>
#include "minishell.h"
#include "libft.h"

int	g_last_code;

static int	do_line(char *str, t_vec_env *env, int *code, int ret)
{
	t_vec_lex	*lex;
	t_vec		*blocks;
	t_pipeline	*pipel;
	int			i;

	if (*str == '\0')
		return (0);
	blocks = split_semicolon(str);
	i = 0;
	ret = 0;
	while (i < (int)blocks->size && ret != 0)
	{
		if (((char **)blocks->arr)[i++][0] != '\0')
		{
			lex = lexer(((char **) blocks->arr)[i - 1]);
			pipel = parser(expand_env(lex, env, *code), &ret, env);
			if (ret != 0)
				ret = executor(pipel, env, code);
			vec_lex_free(lex);
		}
	}
	vec_deep_free(blocks);
	return (ret);
}

static int	main_end(char *str, int res)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (str != NULL)
		free(str);
	printf("exit\n");
	if (res < 0)
		return (-res);
	return (g_last_code);
}

int	main(int argc, char *argv[], char *env[])
{
	char		*str;
	int			res;
	t_vec_env	*ar;

	(void)argc;
	(void)argv;
	g_last_code = 0;
	ar = vec_env_init(env);
	res = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	str = readline("msh$ ");
	while (str != NULL && res >= 0)
	{
		add_history(str);
		res = do_line(str, ar, &g_last_code, 0);
		if (res < 0)
			break ;
		free(str);
		str = readline("msh$ ");
	}
	vec_deep_free((t_vec *)ar);
	return (main_end(str, res));
}
