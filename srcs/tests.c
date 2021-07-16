#include "minishell.h"
#include <stdio.h>
#include <dirent.h>
#include <readline/readline.h>

//int	get_semicolon(char *str, int start);
//
//void	tes(char *str, int start, int needed)
//{
//	static int	num = 0;
//	int			t;
//
//	t = get_semicolon(str, start);
//	if (t != needed)
//		printf("%d: Need %d, get: %d\n", num, needed, t);
//	else
//		printf("%d: ok\n", num);
//	num++;
//}
//
//int	main(void)
//{
//	printf("SEMICOLON INDEX\n");
//	tes("", 0, -1);
//	tes(";", 0, 0);
//	tes(" ;", 0, 1);
//	tes(";;", 1, 1);
//	tes("str;str;", 1, 3);
//	tes("str;str;", 4, 7);
//	tes("str;str", 4, -1);
//}
//
//void	tes(char *str)
//{
//	static int	num = 0;
//	t_vec		*blocks;
//
//	blocks = split_semicolon(str);
//	printf("%d:\n", num);
//	print_strs(((char **)blocks->arr));
//	num++;
//}
//
//int	main(void)
//{
//	printf("SEMICOLON SPLIT\n");
//	tes("");
//	tes("abcdef");
//	tes(";");
//	tes("a;b");
//	tes("a;b;");
//	tes("a;b;cd;");
//	tes("a;b;cd; asfd a;");
//	tes("a;b;cd; asfd a");
//	tes("a;b;cd; asfd\"';'\"a");
//	tes("export abc abc; env; ls | grep -r \\etc");
//}

int	main(void)
{
	t_vec *ret;

	ret = lessless("EOF");
	print_strs(ret->arr);
}