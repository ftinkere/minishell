#ifndef VECTOR_H
# define VECTOR_H
# include "types.h"

t_vecl	*vecl_init();
t_vecl	*vecl_add(t_vecl *vec, t_lex lex);
void	vecl_free(t_vecl *vec);

#endif
