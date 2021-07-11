#include <stdio.h>
#include <stdlib.h>
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
	while (i < blocks->size)
	{
		lexes = lexer(((char**)blocks->arr)[i]);
		res = executor(parser(lexes, vec_env), vec_env);
		vecl_free(lexes);
		if (res <= 0)
			break ;
		i++;
	}
	vec_free_all(blocks);
	return (res);
}

// TODO: promt (?)
// TODO: PATH +-
// TODO: env
// TODO: < > >> &> &>>
// ;, |, ', " works, PATH +-

int	main(int argc, char *argv[], char *env[])
{
	char		*str;
	int			res;
	t_vec_env	*vec_env;

	vec_env = (t_vec_env*)vec_init();
//	env_init(vec_env, env);
	res = 0;
	while (get_next_line(0, &str))
	{
		res = do_line(str, vec_env);
		if (res <= 0)
			break ;
		free(str);
	}
	free(str);
	if (res < 0)
		return (-res);
	return (0);
}
