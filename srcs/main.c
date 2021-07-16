#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "libft.h"

int	do_line(char *str, t_vec_env *env)
{
	t_vec_lex	*lexes;
	t_vec		*blocks;
	int			i;
	int			res;

	blocks = split_semicolon(str);
	i = 0;
	while (i < (int)blocks->size)
	{
		lexes = lexer(((char **)blocks->arr)[i]);
		res = executor(parser(expand_env(lexes, env)), env);
		vecl_free(lexes);
		if (res <= 0)
			break ;
		i++;
	}
	vec_free_all(blocks);
	return (res);
}

// TODO: promt (?) +
// TODO: PATH +-
// TODO: env
// TODO: < > >> <<
// ;, |, ', " works, PATH +-

// SEGFAULT 2+2

//int	main(int argc, char *argv[], char *env[])
//{
//	char	*str;
//	int		res;
//
//	res = 0;
//	while (get_next_line(0, &str))
//	{
//		res = do_line(str, env);
//		if (res <= 0)
//			break ;
//		free(str);
//	}
//	free(str);
//	if (res < 0)
//		return (-res);
//	return (0);
//}

int	main(int argc, char *argv[], char *env[])
{
	char		*str;
	int			res;
	t_vec_env	*ar;

	(void)argc;
	(void)argv;
	ar = env_buildin(env);
	res = 0;
	str = readline("msh: ");
	add_history(str);
	while (str != NULL)
	{
		res = do_line(str, ar);
		if (res <= 0)
			break ;
		free(str);
		str = readline("msh: ");
		add_history(str);
	}
	if (str != NULL)
		free(str);
	if (res < 0)
		return (-res);
	return (0);
}
