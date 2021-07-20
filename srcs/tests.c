#include "minishell.h"
#include <stdio.h>
#include <dirent.h>
#include <readline/readline.h>


int	do_line(char *str, t_vec_env *env)
{
	t_vec_lex	*lexes;
	t_vec		*blocks;
	int			i;
	int			res;

	blocks = split_semicolon(str);
	i = 0;
	while (i < (int)blocks->size)
	{
		lexes = lexer(((char**)blocks->arr)[i]);
		res = executor(parser(expand_env(lexes, env)), env);
		vecl_free(lexes);
		if (res <= 0)
			break ;
		i++;
	}
	vec_free_all(blocks);
	return (res);
}


int	main(void)
{
	t_vec_env *env;
	t_vec_lex *lex;

	env = (t_vec_env *)vec_init();
	do_line("export AAA=123", env);
	lex = expand_env(lexer("echo $AAA"), env);
	print_lexes(lex);
	printf("%s\n", dollar(env->arr, "AAA"));
	do_line("export BBB=$AAA", env);
	printf("%s\n", dollar(env->arr, "BBB"));
//	do_line("env", env);
//	do_line("echo $AAA", env);



}