cmake_minimum_required(VERSION 3.14)
project(my_fdf C)

file(GLOB FILES
        "*.c"
        "*.h"
        #"minilibx_macos/*.h"
        "minilibx_macos/libmlx.a"
        "minilibx_macos/*.c"
        "ft_printf/*.c"
        "ft_printf/ft_printf.h"
        "ft_printf/libft/*.c"
        "ft_printf/libft/libft.h")

set(CMAKE_C_STANDARD 99)
add_definitions(-framework OpenGL -framework AppKit)
add_executable(my_fdf ${FILES} read_file.c)