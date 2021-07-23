#include "minishell.h"
#include "libft.h"

int	ft_count_rows_tab(char **tabl)
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

