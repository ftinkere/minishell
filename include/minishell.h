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
t_pipeline	*parser(t_vec_lex *lexes);
int			executor(t_pipeline *pipeline, t_vec_env *env);

t_vec		*split_semicolon(char *str);
char		*get_path_by_comand(char *cmd);
char		*expand_path_if_need(char *cmd);
t_vec_lex	*expand_env(t_vec_lex *lexes, t_vec_env *env);
t_vec_env 	*vec_env_ch(t_vec_env *env, char *str);
t_vec_env 	*vec_env_rem(t_vec_env *vec, char *key);
t_vec_env 	*vec_env_add(t_vec_env *vec, char *a);

void		print_strs(char **strs);
void		print_lexes(t_vec_lex *vec);
void		free_split(char **strs);
void		free_pipeline(t_pipeline *pipeline);
int			free_ret(void *fred, int ret);
t_vec		*lessless(char *end_str, t_vec *ret);
int			strs_to_in(char **strs);


int			is_buildin(char *str);
int         ft_buildin(t_execve *ar, t_vec_env *env);
t_vec_env 	*env_buildin(char **envp);
char        *dollar(char **tabl, char *key);
int         ft_echo(t_execve *ex);
int    		ft_export_env(t_execve *ex, t_vec_env *env_tab);
int         ft_unset_env(t_execve *arg, t_vec_env *env_tab);
void        ft_cd_buildin(t_execve  *ex);
void        ft_pwd_buildin(t_execve *ex);
size_t      ft_tab_size(char **tabl);
void        print_env(char **tabl);
char        **ins_row(char **tabl, char *str);
char        **del_row(char **tabl, char *str);
int         ft_count_rows_tab(char **tabl);
void        print_export_env(char **tabl);
char        *str_key(char *str);
int         ft_cmp_key(char **tabl, char *key);
char        **ft_cpy_val(char **tabl, char *key);
char        *ft_strdup_prob(char *src);

#endif
