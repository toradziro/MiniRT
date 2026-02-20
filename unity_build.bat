clang -Werror -Wall -Wextra -std=c11 -march=native -O3 -DRT_WIN32 -DTHREADS_MAX=12 srcs/main.c -luser32 -lgdi32 -lkernel32 -o MiniRT.exe
