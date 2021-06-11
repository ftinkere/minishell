#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>

# define S_GREATE ">"
# define S_LESS "<"
# define S_GREATEGREATE ">>"
# define S_LESSLESS "<<"
# define S_GREATEAMP ">&"
# define S_GREATEGREATEAMP ">>&"
# define S_PIPE "|"
# define S_AMP "&"
# define S_SEMICOLON ";"

enum e_token {
	T_WORD = 0,
	T_GREATE,
	T_LESS,
	T_LESSLESS,
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
}	t_vec_lex;


typedef struct s_vec {
	size_t	capacity;
	size_t	size;
	void	*arr;
}	t_vec;
typedef t_vec t_vec_int;

typedef struct s_execve {
	char	*path;
	char	**argv;
}	t_execve;

/*
**
** lexes хранит вектор простых лексем, который был считан со входа
**
** Пара индексов в args говорит начало команды в пайплайне и количество
** лексем которые ей передаются
** a b | c d e | f
** [0; 2] [3; 3] [7; 1]
** С нулевого аргумента два, с третьего три и с седьмого один
**
** execves хранит вектор типа t_execve и представляет собой последовательность
** простых команд в пайплайне которые должны запускаться друг за другом
**
** file_in, file_out, file_err хранят пути к файлам для ввода-вывода этих потоков
**
** wait показывает нужно ли ждать выполнения процесса с команды или нет
**
*/
typedef struct s_pipeline {
	t_vec_lex	*lexes;
	t_vec_int	*args;

	t_vec		*execves;

	t_vec		*envp;

	char		*file_in;
	char		*file_out;
	int			redir_err;
	int			append_out;
	int			wait;
}	t_pipeline;

#endif
