#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

void	print_strs(char *strs[])
{
	int	t;

	t = 0;
	while (strs[t] != NULL)
		printf("%s\n", strs[t++]);
}

void	print_lexes(t_vec_lex *vec)
{
	int	i;

	i = 0;
	while (i < vec->size)
	{
		printf("%s:%i ", vec->arr[i].str, vec->arr[i].token);
		i++;
	}
	printf("\n");
}

/*
** move semantics
*/
void	do_line(char *str, char **env)
{
	t_vec_lex	*lexes;

	lexes = lexer(str);
	expander(lexes, env);
	executor(parser(lexes, env), env);
	vecl_free(lexes);
	free(str);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*str;

	while (get_next_line(0, &str))
	{
		do_line(str, env);
	}
	free(str);
	return (0);
}
