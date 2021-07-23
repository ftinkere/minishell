#include "minishell.h"
#include "libft.h"

int	count_tab_rows(char **tabl)
{
	int	count;

	count = 0;
	while (*tabl)
	{
		count++;
		tabl++;
	}
	return (count);
}
