#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>

# define S_GREATE ">"
# define S_LESS "<"
# define S_GREATEGREATE ">>"
# define S_LESSLESS "<<"
# define S_PIPE "|"
# define MOD_APP (O_CREAT|O_WRONLY|O_APPEND)
# define MOD (O_CREAT|O_WRONLY|O_TRUNC)
# define RIGHTS (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

enum e_token {
	T_WORD = 0,
	T_GREATE,
	T_LESS,
	T_LESSLESS,
	T_GREATGREATE,
	T_PIPE
};

enum e_err_type {
	ERR_MALLOC
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
	void	**arr;
}	t_vec;
typedef t_vec	t_vec_int;

typedef struct s_vec_env {
	size_t	capacity;
	size_t	size;
	char	**arr;
}	t_vec_env;

typedef struct s_execve {
	char	*path;
	char	**argv;
	int		fin;
	int		fout;
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
*/
typedef struct s_pipeline {
	t_vec_lex	*lexes;
	t_vec_int	*args;

	t_vec		*execves;
}	t_pipeline;

typedef struct s_files {
	int		tmpin;
	int		tmpout;
}	t_files;

#endif
