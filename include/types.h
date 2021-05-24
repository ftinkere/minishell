#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>

# define S_GREATE ">"
# define S_LESS "<"
# define S_GREATEGREATE ">>"
# define S_GREATEAMP ">&"
# define S_GREATEGREATEAMP ">>&"
# define S_PIPE "|"
# define S_AMP "&"
# define S_SEMICOLON ";"

enum e_token {
	T_WORD = 0,
	T_GREATE,
	T_LESS,
	T_GREATGREATE,
	T_GREATEAMP,
	T_GREATGREATEAMP,
	T_PIPE,
	T_AMP,
	T_SEMICOLON
};

typedef struct s_lex {
	enum e_token	token;
	char			*str;
}	t_lex;

typedef struct s_vecl {
	size_t	capacity;
	size_t	size;
	t_lex	*arr;
}	t_vecl;

/*
**
** Пара в args_index_pairs говорит начало команды в пайплайне и количество
** лексем которые ей передаются
** a b | c d e | f
** [0; 2] [3; 3] [7; 1]
** С нулевого аргумента два, с третьего три и с седьмого один
**
*/
typedef struct s_exec {
	t_vecl		*lexes;
	size_t		size;
	int			*args_index_pairs;

	int			stdin;
	int			stdout;
	int			stderr;
	int			wait;

	char		*path;
	char		**argv;
	char		**env;
}	t_exec;

#endif
