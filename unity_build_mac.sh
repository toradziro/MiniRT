#!/bin/bash
clang -Werror -Wall -Wextra -std=c11 -march=native -O3 `sdl2-config --cflags` -DRT_LINUX -DMAC_OS -DTHREADS_MAX=10 srcs/main.c -lm `sdl2-config --libs` -o MiniRT
# clang -Werror -Wall -Wextra -std=c11 -march=native -g -fsanitize=address `sdl2-config --cflags` -DRT_LINUX -DMAC_OS -DTHREADS_MAX=12 srcs/main.c -lm `sdl2-config --libs` -o MiniRT
# clang -Werror -Wall -Wextra -std=c11 -march=native -g `sdl2-config --cflags` -DRT_LINUX -DMAC_OS -DTHREADS_MAX=12 srcs/main.c -lm `sdl2-config --libs` -o MiniRT
