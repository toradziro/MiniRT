NAME =		MiniRT

HEAD =		./srcs/includes/

SRC =		srcs/gnl/get_next_line.c \
			srcs/gnl/get_next_line_utils.c \
			srcs/lists_funcs/list_camera_funcs.c \
			srcs/lists_funcs/list_figures_funcs.c \
			srcs/lists_funcs/list_lights_func.c \
			srcs/parser/parser.c \
			srcs/parser/utils.c \
			srcs/parser/figures_creation.c \
			srcs/utilits/killed_by_error.c \
			srcs/vectors_funcs/cross_prod.c \
			srcs/vectors_funcs/new_vector.c \
			srcs/vectors_funcs/vector_length.c \
			srcs/vectors_funcs/vector_normalise.c \
			srcs/vectors_funcs/vector_scalar_mult.c \
			srcs/vectors_funcs/vectors_add_substract.c \
			srcs/ray_trace/ray_trace.c \
			srcs/vectors_funcs/place_camera.c \
			srcs/threads.c \
			srcs/lists_funcs/array_funcs.c \
			srcs/intersec/interset.c \
			srcs/save_to_bmp.c \
			srcs/main.c

OBJS =		${SRC:.c=.o}

CFLAGS	= -g -fsanitize=undefined -Werror -Wall -Wextra -msse3 -O3 -I $(HEAD) -I ./mlx/ -D THREADS_MAX=$(NUM_THREADS)

FLAGS = -msse3 -O3 -Lmlx -lmlx -framework OpenGL -framework AppKit

RM =		rm -rf

CC =		gcc

NUM_THREADS = $(shell sysctl -n hw.ncpu)

$(NAME):	$(OBJS)
			cd mlx && $(MAKE) && mv libmlx.dylib ..
			$(CC) $(CFLAGS) $(OBJS) $(FLAGS) libmlx.dylib -o $(NAME)

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

bonus:

re:			fclean all

#.SILENT:
