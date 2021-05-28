#ifndef MINISHELL_H
# define MINISHELL_H
# include "types.h"


t_vec_lex	*vecl_init(void);
t_vec_lex	*vecl_add(t_vec_lex *vec, t_lex lex);
void		vecl_free(t_vec_lex *vec);

t_vec		*vec_init(void);
t_vec		*vec_add(t_vec *vec, void *a);
void		vec_free(t_vec *vec);
void		vec_free_all(t_vec *vec);

t_vec		*vec_int_init(void);
t_vec		*vec_int_grow(t_vec *vec);
t_vec		*vec_int_add(t_vec *vec, int a);
void		vec_int_free(t_vec *vec);

t_pipeline	*pipeline_init();

t_vec_lex	*lexer(char *str);
t_vec_lex	*expander(t_vec_lex *lexes, char **env);
t_pipeline 	*parser(t_vec_lex *lexes, char **env);
void		executor(t_pipeline *pipeline, char **env);

void	print_strs(char *strs[]);

#endif
