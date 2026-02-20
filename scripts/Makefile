NAME =		MiniRT

HEAD =		./srcs/includes/

SRC =		srcs/lists_funcs/list_camera_funcs.c \
			srcs/lists_funcs/list_lights_func.c \
			srcs/parser/parser.c \
			srcs/parser/parse_utils.c \
			srcs/parser/utils.c \
			srcs/parser/figures_creation.c \
			srcs/utilits/killed_by_error.c \
			srcs/ray_trace/ray_trace.c \
			srcs/vectors_funcs/place_camera.c \
			srcs/render/render.c \
			srcs/lists_funcs/array_funcs.c \
			srcs/save_to_bmp.c \
			srcs/hooks_utils.c \
			srcs/arena/arena.c \
			srcs/string/rt_string.c \
			srcs/file/rt_file.c \
			srcs/bvh/bvh.c \
			srcs/color/color.c \
			srcs/tests/test_bvh.c \
			srcs/main.c

OBJS =		${SRC:.c=.o}

#-fsanitize=address
# CFLAGS	= -Werror -Wall -Wextra -std=c11 -g -fsanitize=address -I $(HEAD) `sdl2-config --cflags` -D THREADS_MAX=$(NUM_THREADS)
CFLAGS	= -Werror -Wall -Wextra -std=c11 -march=native -O3 -I $(HEAD) `sdl2-config --cflags` -D THREADS_MAX=$(NUM_THREADS)
# CFLAGS	= -Werror -Wall -Wextra -std=c11 -march=native -O3 -DTESTS -I $(HEAD) `sdl2-config --cflags` -D THREADS_MAX=$(NUM_THREADS)

FLAGS = 	-lm `sdl2-config --libs`

RM =		rm -rf

CC =		gcc

NUM_THREADS = 12

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(FLAGS) -o $(NAME)

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

bonus:

re:			fclean all

#.SILENT:
