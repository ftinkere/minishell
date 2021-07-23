#include <stdlib.h>

int	free_ret(void *fred, int ret)
{
	free(fred);
	return (ret);
}
