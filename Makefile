NAME =		MiniRT

HEAD =		./includes/

SRC =		gnl/get_next_line.c \
			gnl/get_next_line_utils.c \
			lists_funcs/list_camera_funcs.c \
			lists_funcs/list_figures_funcs.c \
			lists_funcs/list_lights_func.c \
			parser/parser.c \
			parser/utils.c \
			parser/figures_creation.c \
			utilits/killed_by_error.c \
			vectors_funcs/cross_prod.c \
			vectors_funcs/new_vector.c \
			vectors_funcs/vector_by_matrix.c \
			vectors_funcs/vector_length.c \
			vectors_funcs/vector_normalise.c \
			vectors_funcs/vector_scalar_mult.c \
			vectors_funcs/vectors_add_substract.c \
			ray_trace/ray_trace.c \
			ray_trace/print_scene.c \
			vectors_funcs/place_camera.c \
			threads.c \
			main.c

OBJS =		${SRC:.c=.o}

CFLAGS	= -Wall -Wextra -msse3 -O3 -I $(HEAD) -I ./mlx/ -D THREADS_MAX=$(NUM_THREADS)

MLX_MAC_FLAGS =	-Lmlx -lmlx -framework OpenGL -msse3 -O3 -framework AppKit

MLX_LNX_FLAGS =	-Lmlx_Linux -msse3 -O3 -lmlx_Linux -L/usr/lib -Imlx_Linux -lXext -lX11 -lm -lz -lpthread

RM =		rm -rf

CC =		gcc -g

UNAME :=	$(shell uname)

#for debug -fsanitize=address -g $(shell sysctl -n hw.ncpu)
ifeq ($(UNAME),Darwin)
	NUM_THREADS = $(shell sysctl -n hw.ncpu)
	FLAGS = $(MLX_MAC_FLAGS)
endif

ifeq ($(UNAME),Linux)
	NUM_THREADS = $(shell nproc --all)
	FLAGS = $(MLX_LNX_FLAGS)
endif

$(NAME):	${OBJS}
			${CC} ${CFLAGS} $(OBJS) $(FLAGS) -o ${NAME}

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.SILENT:
