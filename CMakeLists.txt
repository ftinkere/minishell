cmake_minimum_required(VERSION 3.19)
project(minishell C)

set(CMAKE_C_STANDARD 99)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libft /usr/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libft ${CMAKE_CURRENT_SOURCE_DIR}/include /usr/include)

add_custom_target(libft
        COMMAND make all
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libft
        )


add_executable(minishell srcs/main.c srcs/lexer.c include/types.h srcs/vec_lex/vec_lex_free.c include/minishell.h srcs/env/env_get_value.c srcs/parser/parser.c srcs/expander/expand_env.c srcs/executor/executor.c srcs/utils/pipeline_init.c srcs/vec_int/vec_int_free.c srcs/utils/prints.c srcs/utils/split_semicolon.c srcs/expander/expand_path.c srcs/utils/exit_err.c srcs/parser/lessless.c srcs/buildins/buildin_pwd.c srcs/utils/count_tab_rows.c srcs/utils/signal_handlers.c srcs/buildins/buildin_echo.c srcs/buildins/buildin_export.c srcs/buildins/buildin_export_print.c srcs/buildins/buildin_unset.c srcs/buildins/buildin_cd.c srcs/buildins/buildin_exit.c srcs/buildins/buildin_dispatcher.c srcs/buildins/buildin_env.c srcs/vec_env/vec_env_init.c srcs/env/str_get_key.c srcs/env/env_key_chr.c srcs/vec_env/vec_env_add.c srcs/vec_env/vec_env_rem.c srcs/vec_env/vec_env_ch.c srcs/vec_env/vec_env_join.c srcs/vec/vec_init.c srcs/vec/vec_grow.c srcs/vec/vec_add.c srcs/vec/vec_free.c srcs/vec/vec_deep_free.c srcs/vec_lex/vec_lex_init.c srcs/vec_lex/vec_lex_grow.c srcs/vec_lex/vec_lex_add.c srcs/vec_int/vec_int_init.c srcs/vec_int/vec_int_grow.c srcs/vec_int/vec_int_add.c srcs/free/free_ret.c srcs/free/free_split.c srcs/free/free_execves.c srcs/free/free_pipeline.c srcs/buildins/is_buildin.c srcs/utils/is_comand.c srcs/executor/executor_minis.c srcs/utils/t_execve_init.c srcs/parser/piper.c srcs/parser/add_greategreate.c srcs/parser/add_greate.c srcs/parser/add_lessless.c srcs/parser/add_less.c srcs/parser/check_err_redirect.c srcs/utils/get_execve.c srcs/utils/get_args.c srcs/parser/count_args.c srcs/parser/count_pipes.c srcs/vec_env/str_key.c)
add_executable(minishell_tester srcs/tests.c srcs/lexer.c include/types.h srcs/vec_lex/vec_lex_free.c include/minishell.h srcs/env/env_get_value.c srcs/parser/parser.c srcs/expander/expand_env.c srcs/executor/executor.c srcs/utils/pipeline_init.c srcs/vec_int/vec_int_free.c srcs/utils/prints.c srcs/utils/split_semicolon.c srcs/expander/expand_path.c srcs/utils/exit_err.c srcs/parser/lessless.c srcs/buildins/buildin_pwd.c srcs/utils/count_tab_rows.c srcs/utils/signal_handlers.c srcs/buildins/buildin_echo.c srcs/buildins/buildin_export.c srcs/buildins/buildin_export_print.c srcs/buildins/buildin_unset.c srcs/buildins/buildin_cd.c srcs/buildins/buildin_exit.c srcs/buildins/buildin_dispatcher.c srcs/vec_env/vec_env_init.c srcs/env/env_key_chr.c srcs/vec_env/vec_env_add.c srcs/vec_env/vec_env_rem.c srcs/vec_env/vec_env_ch.c srcs/vec/vec_init.c srcs/vec/vec_grow.c srcs/vec/vec_add.c srcs/vec/vec_free.c srcs/vec/vec_deep_free.c srcs/vec_lex/vec_lex_init.c srcs/vec_lex/vec_lex_add.c srcs/vec_int/vec_int_init.c srcs/vec_int/vec_int_grow.c srcs/vec_int/vec_int_add.c srcs/free/free_ret.c srcs/free/free_split.c srcs/free/free_execves.c srcs/free/free_pipeline.c srcs/utils/is_comand.c srcs/executor/executor_minis.c srcs/utils/t_execve_init.c srcs/parser/piper.c srcs/parser/add_greategreate.c srcs/parser/add_greate.c srcs/parser/add_lessless.c srcs/parser/add_less.c srcs/parser/check_err_redirect.c srcs/utils/get_execve.c srcs/utils/get_args.c srcs/parser/count_args.c srcs/parser/count_pipes.c srcs/vec_env/str_key.c)
add_dependencies(minishell libft)
add_dependencies(minishell_tester libft)
target_link_libraries(minishell ft readline)
target_link_libraries(minishell_tester ft readline)