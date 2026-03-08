/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:10:38 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/21 00:06:42 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "../arena/arena.h"
#include "../string/rt_string.h"
#include "../includes/scene.h"

void     parse_primitives(char* str, t_scene* scene, t_memory_arena* arena);
void     start_parse(t_scene* scene, str8 path, t_memory_arena* arena);
char*    skip_spaces(char* str);
char*    skip_pattern(char* str);
char*    skip_nums(char* str);
t_vector parse_coordinares(char* str);
void     parse_size(char* str, t_scene* scene);
void     parse_ambl(char* str, t_scene* scene, t_memory_arena* arena);
void     parse_cam(char* str, t_scene* scene, t_memory_arena* arena);
void     parse_light(char* str, t_scene* scene, t_memory_arena* arena);
void     parse_triangle(char* str, t_scene* scene);
t_color  new_color(int r, int g, int b);

#endif
