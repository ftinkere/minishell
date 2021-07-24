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
int			vec_deep_free(t_vec *vec);

/*
** Vector of lexes
*/
t_vec_lex	*vec_lex_init(void);
t_vec_lex	*vec_lex_grow(t_vec_lex *vec);
t_vec_lex	*vec_lex_add(t_vec_lex *vec, t_lex lex);
int			vec_lex_free(t_vec_lex *vec);

/*
** Vector of ints
*/
t_vec		*vec_int_init(void);
t_vec		*vec_int_grow(t_vec *vec);
t_vec		*vec_int_add(t_vec *vec, int a);
void		vec_int_free(t_vec *vec);

/*
** Init of structures
*/
t_pipeline	*pipeline_init(void);
t_execve	*t_execve_init(void);

/*
** Lexer
*/
t_vec_lex	*lexer(char *str);
t_vec		*split_semicolon(char *str);

/*
** Parser
*/
t_pipeline	*parser(t_vec_lex *lexes, int *ret, t_vec_env *env);
int			read_lessless__ret_fd(char *end_str);
int			piper(t_pipeline *pipel, int *pipe_n, t_vec_lex *lex, int i);
int			add_greategreate(t_execve *ex, t_vec_lex *lex, int i);
int			add_greate(t_execve *ex, t_vec_lex *lex, int i);
int			add_lessless(t_execve *ex, t_vec_lex *lex, int i);
int			add_less(t_execve *ex, t_vec_lex *lex, int i);
int			check_err_redirect(t_vec_lex *lex, int i);
int			count_args(t_vec_lex *lex, int start);
int			count_pipes(t_vec_lex *lexes);
void		set_args(t_pipeline *pipel, t_vec_lex *lex, int args_count, int i);

/*
** Expander
*/
char		*expand_path(char *cmd, t_vec_env *env);
t_vec_lex	*expand_env(t_vec_lex *lexes, t_vec_env *env, int last_code);

/*
** Executor
*/
void		exec_one(t_execve *exec, char **env);
char		*cmd_ex(t_pipeline *pipeline, int i);
pid_t		fork_and_signal_set(void);
int			executor(t_pipeline *pipel, t_vec_env *env, int *last_code);

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
void		buildin_export_print(char **tabl);

/*
** Utils
*/
int			is_comand(char *str);
int			count_tab_rows(char **tabl);
t_execve	*get_execve(t_pipeline *pipeline, int i);
int			get_args(t_pipeline *pipeline, int i);
void		exit_err(enum e_err_type err);
char		*str_key(const char *str);

/*
** Free
*/
void		free_execves(t_vec *execves);
void		free_split(char **strs);
int			free_pipeline(t_pipeline *pipeline);
int			free_ret(void *fred, int ret);

/*
** Print or debug
*/
void		print_strs(char **strs);
void		print_lexes(t_vec_lex *vec);

#endif
