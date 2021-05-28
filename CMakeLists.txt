cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 99)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libft)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libft ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_custom_target(libft
        COMMAND make all
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libft
        )


add_executable(minishell srcs/main.c srcs/lexer.c include/types.h srcs/vecl.c include/minishell.h srcs/env.c srcs/parser.c srcs/expander.c srcs/executor.c srcs/t_pipeline.c srcs/vec.c srcs/vec_int.c)
add_dependencies(minishell libft)
target_link_libraries(minishell ft)