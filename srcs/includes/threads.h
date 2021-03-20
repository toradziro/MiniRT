/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:10:45 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:48:45 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H
# include "minirt.h"

typedef struct		s_thread{
	int				id;
	t_scene			scene;
}					t_thread;

void				*ray_trace_thread(void *thread);
void				threads(t_scene *scene);

#endif
