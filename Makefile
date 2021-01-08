NAME = RT

SRC = main.c utils.c

CC = gcc

FLAGS = -Wall -Wextra -Werror

all:
	${CC} -lmlx -framework OpenGL -framework AppKit ${SRC} -o ${NAME}

clean:
	rm -f RT
