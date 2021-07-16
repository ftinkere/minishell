cmake_minimum_required(VERSION 3.19)
project(minishell C)

set(CMAKE_C_STANDARD 99)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libft)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libft ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_custom_target(libft
        COMMAND make all
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libft
        )


add_executable(minishell srcs/main.c srcs/lexer.c include/types.h srcs/vecl.c include/minishell.h srcs/env.c srcs/parser.c srcs/expander.c srcs/executor.c srcs/t_pipeline.c srcs/vec.c srcs/vec_int.c srcs/prints.c srcs/split_semicolon.c srcs/path.c srcs/utils.c srcs/lessless.c srcs/buildin_fu.c)
add_executable(minishell_tester srcs/tests.c srcs/lexer.c include/types.h srcs/vecl.c include/minishell.h srcs/env.c srcs/parser.c srcs/expander.c srcs/executor.c srcs/t_pipeline.c srcs/vec.c srcs/vec_int.c srcs/prints.c srcs/split_semicolon.c srcs/path.c srcs/utils.c srcs/lessless.c srcs/buildin_fu.c)
add_dependencies(minishell libft)
add_dependencies(minishell_tester libft)
target_link_libraries(minishell ft readline)
target_link_libraries(minishell_tester ft readline)