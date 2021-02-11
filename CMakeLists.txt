cmake_minimum_required(VERSION 3.17)
project(MiniRT C)

set(CMAKE_C_STANDARD 11)

include_directories(gnl)
include_directories(includes)

add_executable(MiniRT
        gnl/get_next_line.c
        gnl/get_next_line.h
        gnl/get_next_line_utils.c
        includes/colors.h
        includes/figures.h
        includes/lists.h
        includes/MiniRT.h
        includes/parser.h
        includes/vectors.h
        includes/vplane.h
        lists_funcs/list_camera_funcs.c
        lists_funcs/list_figures_funcs.c
        lists_funcs/list_lights_func.c
        parser/parser.c
        parser/utils.c
        parser/figures_creation.c
        utilits/killed_by_error.c
        vectors_funcs/cross_prod.c
        vectors_funcs/matrix_decl.c
        vectors_funcs/matrix_multip.c
        vectors_funcs/new_vector.c
        vectors_funcs/vector_by_matrix.c
        vectors_funcs/vector_length.c
        vectors_funcs/vector_normalise.c
        vectors_funcs/vector_scalar_mult.c
        vectors_funcs/vectors_add_substract.c
        main.c)
