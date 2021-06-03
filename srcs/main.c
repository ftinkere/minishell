#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

/*
** move semantics
*/
void	do_line(char *str, char **env)
{
	t_vec_lex	*lexes;
	t_vec		*blocks;
	int			i;

	blocks = split_semicolon(str);
	i = 0;
	while (i < blocks->size)
	{
		lexes = lexer(((char**)blocks->arr)[i]);
		executor(parser(lexes, env), env);
		vecl_free(lexes);
		i++;
	}
	vec_free_all(blocks);
	free(str);
}

// TODO: promt (?)
// TODO: PATH +-
// TODO: env
// TODO: built-in
// TODO: < > >> &> &>>
// ;, |, ', " works, PATH +-

int	main(int argc, char *argv[], char *env[])
{
	char	*str;

	while (get_next_line(0, &str)) //freed
	{
		do_line(str, env);
	}
	free(str);
	return (0);
}
