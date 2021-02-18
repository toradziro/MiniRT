NAME =		MiniRT

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
			vectors_funcs/matrix_decl.c \
			vectors_funcs/matrix_multip.c \
			vectors_funcs/new_vector.c \
			vectors_funcs/vector_by_matrix.c \
			vectors_funcs/vector_length.c \
			vectors_funcs/vector_normalise.c \
			vectors_funcs/vector_scalar_mult.c \
			vectors_funcs/vectors_add_substract.c \
			ray_trace/ray_trace.c \
			main.c

OBJS =		${SRC:.c=.o}
MAC_FLAGS =	-Lmlx -lmlx -framework OpenGL -framework AppKit
LNX_FLAGS =	-Lmlx -lmlx -Imlx -lXext -lX11 -lm -lz
RM =		rm -rf
CC =		gcc

all:		$(NAME)

#MAC
#%.o: %.c
#			$(CC) -Wall -Wextra -Werror -I ./includes/ -I ./mlx/ -c $< -o $@
#
#$(NAME):	${OBJS}
#			$(CC) $(MAC_FLAGS) $(OBJS) -o $(NAME)

#LINUX
%.o: %.c
			$(CC) -Wall -Wextra -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -Lmlx_Linux -lmlx_Linux -L/usr/lib -Imlx_Linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all
