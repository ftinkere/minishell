#include "minishell.h"
#include <stdio.h>
#include <dirent.h>
#include <readline/readline.h>

int	do_line(char *str, t_vec_env *env, int *last_code)
{
	t_vec_lex	*lexes;
	t_pipeline	*pipe;
	int			ret_redirect;
	int			ret;

	if (*str == '\0')
		return (0);
	lexes = lexer(str);
	pipe = parser(expand_env(lexes, env, *last_code), &ret_redirect, &ret, env);
	if (ret_redirect)
		return (ret_redirect);
	if (ret)
		return (ret);
	ret = executor(pipe, env, last_code);
	vecl_free(lexes);
	return (ret);
}

int	main(void)
{
	int			last_code;
	t_vec_env	*env;
	t_vec_lex	*lex;

	last_code = 0;
	env = (t_vec_env *)vec_init();
	do_line("echo $?", env, &last_code);
	do_line("cd sad a", env, &last_code);
	do_line("echo $?", env, &last_code);
//	printf("%s\n", dollar(env->arr, "?", 10));
//	printf("%s\n", dollar(env->arr, "?", 0));
	//	do_line("export END_TOKEN=EOF", env);
//	lex = expand_env(lexer("echo $AAA"), env);
//	print_lexes(lex);
//	printf("%s\n", dollar(env->arr, "AAA"));
//	do_line("cat << $END_TOKEN", env);
//	printf("%s\n", dollar(env->arr, "BBB"));
//	do_line("env", env);
//	do_line("echo $AAA", env);



}