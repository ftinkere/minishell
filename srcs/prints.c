#include "minishell.h"
#include <stdio.h>

void	print_strs(char **strs)
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
	while (i < (int)vec->size)
	{
		printf("%s:%i ", vec->arr[i].str, vec->arr[i].token);
		i++;
	}
	printf("\n");
}