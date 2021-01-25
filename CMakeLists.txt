cmake_minimum_required(VERSION 3.17)
project(cmsh C)

set(CMAKE_C_STANDARD 99)

add_executable(cmsh src/main.c
        src/utils/env_tools.c
        src/utils/env_tools_2.c
        src/utils/strarr_tools.c
        src/utils/error_tools.c
        src/process.c
        src/builtin/builtin.c
        src/builtin/echo_main.c
        src/builtin/env_main.c
        src/builtin/pwd_main.c
        src/builtin/cd_main.c
        src/builtin/unset_main.c
        src/builtin/export_main.c
        src/builtin/exit_main.c
        src/lexer/lexer.c
        src/lexer/lexer_2.c
        src/lexer/lexer_utils.c
        src/lexer/lexer_utils_2.c
        src/parser/parser.c
        src/utils/exit_failure.c
        src/utils/get_full_name.c
        src/utils/fd_tools.c
        src/utils/handlers.c
        src/utils/prompt_tools.c
        src/parser/parser_utils.c
        src/parser/parser_utils_2.c
        src/parser/parser_2.c
        src/parser/parser_3.c
        )

include_directories(libft/include include libft)
#find_library(LIBFT_G ft "${CMAKE_SOURCE_DIR}/libft/")
find_library(LIBFT_G ft "/Users/sbashir/intra/final_minishell/libft/")
target_link_libraries(cmsh ${LIBFT_G})
#find_library(Test_LIB test "${CMAKE_SOURCE_DIR}/libs/lib")
SET(CMAKE_CXX_FLAGS  "-Wall -Wextra -Werror")