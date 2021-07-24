# Name
NAME	=	minishell

# External tools
SHELL	=	/bin/sh
CC		=	clang

CFLAGS	=	-Werror -Wall -Wextra \
	-I. -Iinclude -Ilibft
LIBS	=	-Llibft -lft -lreadline

# Sources
SOURCES	=	srcs/main.c srcs/lexer.c srcs/vec_env/str_key.c \
srcs/vec_lex/vec_lex_free.c srcs/env/env_get_value.c srcs/parser/count_pipes.c \
srcs/parser/parser.c srcs/expander/expand_env.c srcs/executor/executor.c \
srcs/utils/pipeline_init.c srcs/vec_int/vec_int_free.c srcs/utils/prints.c \
srcs/utils/split_semicolon.c srcs/expander/expand_path.c srcs/utils/exit_err.c \
srcs/parser/lessless.c srcs/buildins/buildin_pwd.c srcs/utils/count_tab_rows.c \
srcs/utils/signal_handlers.c srcs/buildins/buildin_echo.c \
srcs/buildins/buildin_export.c srcs/buildins/buildin_export_print.c \
srcs/buildins/buildin_unset.c srcs/buildins/buildin_cd.c \
srcs/buildins/buildin_exit.c srcs/buildins/buildin_dispatcher.c \
srcs/buildins/buildin_env.c srcs/vec_env/vec_env_init.c srcs/env/str_get_key.c \
srcs/env/env_key_chr.c srcs/vec_env/vec_env_add.c srcs/vec_env/vec_env_rem.c \
srcs/vec_env/vec_env_ch.c srcs/vec_env/vec_env_join.c srcs/vec/vec_init.c \
srcs/vec/vec_grow.c srcs/vec/vec_add.c srcs/vec/vec_free.c \
srcs/vec/vec_deep_free.c srcs/vec_lex/vec_lex_init.c \
srcs/vec_lex/vec_lex_grow.c srcs/vec_lex/vec_lex_add.c \
srcs/vec_int/vec_int_init.c srcs/vec_int/vec_int_grow.c \
srcs/vec_int/vec_int_add.c srcs/free/free_ret.c srcs/free/free_split.c \
srcs/free/free_execves.c srcs/free/free_pipeline.c srcs/buildins/is_buildin.c \
srcs/utils/is_comand.c srcs/executor/executor_minis.c \
srcs/utils/t_execve_init.c srcs/parser/piper.c srcs/parser/add_greategreate.c \
srcs/parser/add_greate.c srcs/parser/add_lessless.c srcs/parser/add_less.c \
srcs/parser/check_err_redirect.c srcs/utils/get_execve.c srcs/utils/get_args.c \
srcs/parser/count_args.c

INCLUDES = include/types.h include/minishell.h

all: $(NAME)

allc: all clean

bonus: all

fclean: clean
	$(MAKE) -C libft fclean
	@rm -f $(NAME)
	@echo -e "\x1b[38;5;3m""FCleaned $(NAME)""\x1b[0m"

clean:
	$(MAKE) -C libft clean
	@echo -e "\x1b[38;5;3m""Cleaned $(NAME)""\x1b[0m"

re: fclean all

beep:
	@echo -e "\07"

$(NAME): $(SOURCES) $(INCLUDES)
	$(MAKE) -C libft all
	$(CC) -o $(NAME) $(CFLAGS) $(SOURCES) $(LIBS)
	@echo -e "\x1b[38;5;6m""Maked $@""\x1b[0m"
