#include <types.h>

int	count_pipes(t_vec_lex *lexes)
{
	int	ret;
	int	i;

	ret = 1;
	i = 0;
	while (i < (int)lexes->size)
	{
		if (lexes->arr[i].token == T_PIPE)
			ret++;
		i++;
	}
	return (ret);
}
