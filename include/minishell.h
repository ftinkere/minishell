#ifndef MINISHELL_H
# define MINISHELL_H
# include "types.h"


t_vecl	*vecl_init(void);
t_vecl	*vecl_add(t_vecl *vec, t_lex lex);
void	vecl_free(t_vecl *vec);

t_vecl	*lexer(char *str);
t_vecl	*expander(t_vecl *lexes, char **env);
t_exec	*parser(t_vecl *lexes, char **env);
void	executor(t_exec *exec, char **env);

#endif
