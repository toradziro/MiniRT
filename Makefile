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
			main.c

OBJS =		${SRC:.c=.o}
FLAGS =		-Wall -Wextra -Werror #-lmlx -framework OpenGL -framework AppKit
RM =		rm -rf
CC =		gcc

all:		$(NAME)

.c.o:
			$(CC) $(FLAGS) -I ./includes -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			$(CC) $(FLAGS) -I ./includes $(SRC) -o $(NAME) -lm

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}