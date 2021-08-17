/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:17:23 by ehillman          #+#    #+#             */
/*   Updated: 2020/11/13 18:50:41 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
char	*ft_strjoin(char *s1, char *s2);
int		ft_find_endl(char *tmp);
char	*ft_init(char *rem);
char	*ft_cut(char *rem);
int		ft_strlen(char *s);
void	*ft_calloc(size_t num, size_t size);
void	*ft_memset(void *dest, int c, size_t n);
int		ft_count_to_endl(char *s);
int		ft_free(char *tmp);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif
