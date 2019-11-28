cmake_minimum_required(VERSION 3.14)
project(my_fdf C)

file(GLOB FILES
        "*.c"
        "*.h"
        "minilibx_macos/libmlx.a"
        "ft_printf/*.c"
        "ft_printf/ft_printf.h"
        "ft_printf/libft/*.c"
        "ft_printf/libft/libft.h")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lmlx -framework OpenGL -framework AppKit -L")
set(CMAKE_C_STANDARD 99)
#add_definitions(-Wall -Wextra -Werror)
add_executable(my_fdf ${FILES})