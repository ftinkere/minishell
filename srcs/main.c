#include <stdio.h>
#include "minishell.h"
#include "libft.h"

void	print_strs(char *strs[])
{
	int	t;

	t = 0;
	while (strs[t] != NULL)
		printf("%s\n", strs[t++]);
}

void	print_lexes(t_vecl *vec)
{
	int	i;

	i = 0;
	while (i < vec->size)
	{
		printf("%s:%i ", vec->arr[i].str, vec->arr[i].token);
		i++;
	}
}

int	main(int argc, char *argv[], char *env[]) {
	char	*str;
	t_vecl	*vec;

	get_next_line(0, &str);
	vec = lexer(str);
	print_lexes(vec);
	return (0);
}
