cmake_minimum_required(VERSION 3.17)
project(cmsh C)

set(CMAKE_C_STANDARD 99)

add_executable(cmsh src/main.c src/env_tools.c src/utils/ft_strar.c src/utils/msg_exit.c src/process.c src/builtin/builtin.c
        src/builtin/echo_main.c src/builtin/env_main.c src/builtin/pwd_main.c src/builtin/cd_main.c)
include_directories(libft/include include libft)
find_library(LIBFT_G ft "${CMAKE_SOURCE_DIR}/libft/")
target_link_libraries(cmsh ${LIBFT_G})
#find_library(Test_LIB test "${CMAKE_SOURCE_DIR}/libs/lib")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIE")