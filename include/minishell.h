#ifndef MINISHELL_H
# define MINISHELL_H
# include "types.h"

/*
** Vector of void *
*/
t_vec		*vec_init(void);
t_vec		*vec_add(t_vec *vec, void *a);
t_vec		*vec_grow(t_vec *vec);
void		vec_free(t_vec *vec);
void		vec_deep_free(t_vec *vec);

/*
** Vector of lexes
*/
t_vec_lex	*vec_lex_init(void);
t_vec_lex	*vec_lex_grow(t_vec_lex *vec);
t_vec_lex	*vec_lex_add(t_vec_lex *vec, t_lex lex);
void		vec_lex_free(t_vec_lex *vec);

/*
** Vector of ints
*/
t_vec		*vec_int_init(void);
t_vec		*vec_int_grow(t_vec *vec);
t_vec		*vec_int_add(t_vec *vec, int a);
void		vec_int_free(t_vec *vec);

t_pipeline	*pipeline_init(void);

t_vec_lex	*lexer(char *str);
t_pipeline	*parser(t_vec_lex *lexes, int *ret_redirect, int *ret_parse,
				t_vec_env *env);
int			executor(t_pipeline *pipel, t_vec_env *env, int *last_code);

t_vec		*split_semicolon(char *str);
//char		*get_path_by_comand(char *cmd, t_vec_env *env);
char		*expand_path(char *cmd, t_vec_env *env);
t_vec_lex	*expand_env(t_vec_lex *lexes, t_vec_env *env, int last_code);
int			is_comand(char *str);

void		print_strs(char **strs);
void		print_lexes(t_vec_lex *vec);
t_vec		*lessless(char *end_str, t_vec *ret);
int			strs_to_in(t_vec *strs);
int			ret_lessless_fd(char *end_str);
int			ft_count_rows_tab(char **tabl);
void		print_export_env(char **tabl);
t_execve	*get_execve(t_pipeline *pipeline, int i);
void		exit_err(enum e_err_type err);

/*
** Signal handlers
*/
void		sigint_handler(__attribute__((unused)) int status);
void		sigint_proc_handler(__attribute__((unused)) int status);
void		sigquit_proc_handler(__attribute__((unused)) int status);

/*
** Vector of envs
*/
t_vec_env	*vec_env_init(char **envp);
t_vec_env	*vec_env_ch(t_vec_env *env, char *str);
t_vec_env	*vec_env_add(t_vec_env *env, char *str);
t_vec_env	*vec_env_join(t_vec_env *env, char *str);
t_vec_env	*vec_env_rem(t_vec_env *env, char *key);

/*
** Env
*/
char		*env_get_value(char **tabl, char *key, int last_code);
int			env_keychr(char **tabl, char *key);
char		*str_get_key(const char *str);


/*
** Buildins
*/
int			is_buildin(char *str);
int			buildin_dispath(t_execve *ex, t_vec_env *env, int *last_code,
				int is_pipe);
int			buildin_echo(t_execve *ex);
int			buildin_export(t_execve *ex, t_vec_env *env, int num_cmds);
int			buildin_unset(t_execve *ex, t_vec_env *env);
int			buildin_cd(t_execve *ex, t_vec_env *env);
int			buildin_pwd(t_execve *ex);
int			buildin_env(char **tabl);
void		buildin_exit(t_execve *ex);

/*
** Free
*/
void		free_execves(t_vec *execves);
void		free_split(char **strs);
void		free_pipeline(t_pipeline *pipeline);
int			free_ret(void *fred, int ret);

#endif
