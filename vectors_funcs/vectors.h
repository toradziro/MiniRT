#ifndef VECTORS_H
# define VECTORS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	t_vector {
				double v_x;
				double v_y;
				double v_z;
}				s_vector;

typedef struct	t_point {
				double p_x;
				double p_y;
				double p_z;
}				s_point;

typedef struct	t_normal {
				double n_x;
				double n_y;
				double n_z;
}				s_normal;

#endif
