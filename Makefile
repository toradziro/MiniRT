NAME =		MiniRT

SRC =		./vectors_funcs/*.c \
			./figur_list/*.c intersec/*.c ray_trace/*.c \
			./scene/*.c ./utilits/*.c \
			main.c

OBJS =		*.o #${SRC:.c=.o}

FLAGS =		-lmlx -framework OpenGL -framework AppKit

CC =		gcc

.c.o:
	${CC} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${CC} ${FLAGS} ${SRC}

all:	${NAME}
