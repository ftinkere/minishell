#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/signal.h>
#include "minishell.h"
#include "libft.h"

int	do_line(char *str, t_vec_env *env, int *last_code)
{
	t_vec_lex	*lexes;
	t_vec		*blocks;
	t_pipeline	*pipel;
	int			i;
	int			ret_redirect;
	int			ret;

	if (*str == '\0')
		return (0);
	blocks = split_semicolon(str);
	i = 0;
	while (i < blocks->size)
	{
		lexes = lexer(((char **)blocks->arr)[i]);
		pipel = parser(expand_env(lexes, env, *last_code),
				&ret_redirect, &ret, env);
		if (ret_redirect)
			return (ret_redirect);
		if (ret)
			return (ret);
		ret = executor(pipel, env, last_code);
		vecl_free(lexes);
		i++;
	}
	vec_free_all(blocks);
	return (ret);
}

// TODO: signals, ctrl D done
// TODO: exit codes of buildins
// TODO: fork buildins in pipeline

//TODO: change promt to msh after test
int	main(int argc, char *argv[], char *env[])
{
	char		*str;
	int			res;
	t_vec_env	*ar;
	int			last_code;

	(void)argc;
	(void)argv;
	last_code = 0;
	ar = env_buildin(env);
	res = 0;
	str = readline("bash-5.1$ ");
//	add_history(str);
	while (str != NULL && res >= 0)
	{
		add_history(str);
		res = do_line(str, ar, &last_code);
		if (res < 0)
			break ;
		free(str);
		str = readline("bash-5.1$ ");
	}
	if (str != NULL)
		free(str);
	printf("exit\n");
	if (res < 0)
		return (-res);
	return (last_code);
}
