/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 12:24:11 by ehillman          #+#    #+#             */
/*   Updated: 2020/11/13 18:52:26 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char				*ft_strjoin(char *s1, char *s2)
{
	char			*new;
	char			*tmp;
	int				i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!(new = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	tmp = new;
	while (s1 && s1[i])
	{
		*new = s1[i];
		new++;
		i++;
	}
	if (s1)
		free(s1);
	while (s2 && *s2)
	{
		*new = *s2;
		new++;
		s2++;
	}
	return (tmp);
}

int					ft_strlen(char *s)
{
	int				i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

void				*ft_calloc(size_t num, size_t size)
{
	void			*res;

	res = (char*)malloc(num * size);
	if (!res)
		return (NULL);
	ft_memset(res, 0, (num * size));
	return (res);
}

void				*ft_memset(void *dest, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char*)dest;
	while (i < n)
	{
		*str = c;
		str++;
		i++;
	}
	return (dest);
}

int					ft_free(char *tmp)
{
	free(tmp);
	return (-1);
}
