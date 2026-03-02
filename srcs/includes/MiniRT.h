/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:22:04 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 23:50:01 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H
#include "../vectors_funcs/rt_math.h"
#include "../parser/parser.h"
#include "figures.h"
#include "my_types.h"

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define ABS(a) ((a) > (0)) ? (a) : (-a)

#define MIN_I 0.004

#define MALLOC_ERROR -1
#define INV_AM_OF_ARG -2
#define INV_FILE_NAME -3
#define INV_COLOR -4
#define UNKNWN_ARG -5
#define NOT_ENOUGH -6

#define MAX_COLOR 255

/* #define TRACE \
    printf("%d %s %s\n", __LINE__, __FILE__, __FUNCTION__);                                                            \
    fflush(stdout);
*/

void    killed_by_error(int num);
void    check_valid_name(char* str);
float   d_atoi(char* str);
float   parse_int_part(char* str);
float   parse_d_part(char* str);
t_color col_parse(char* str);
t_color check_valid_color(t_color* c);
void    free_scene(t_scene* scene);

int mouse_press(int b, int x, int y, t_scene* scene);

void check_scene(t_scene* scene);

void save_to_bmp(t_scene* scene);
void init_head(char* head, t_scene* scene, int file_size);

void save_to_bmp(t_scene* scene);
#endif
