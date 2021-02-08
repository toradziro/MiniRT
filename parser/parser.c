/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 23:11:42 by ehillman          #+#    #+#             */
/*   Updated: 2021/02/05 23:11:44 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/MiniRT.h"

/*
 * "R 100 | 100" - x, y are size of render
 * "A 0.2 | 255,255,255" - ambient light, 0,2 is intensity, other is color
 * "c 50.0, 0, 20.0  |  0,1,0 | 70" - camera x,y,z are view point, 3d normalized vector, field of view
 * "l -40.0,50.0,0.0 | 0.6 |  10,0,255" - light x,y,z are coordinates of light point, intensity, color
 * "sp 0.0,0.0,20.0 |  12.6 |  10,0,255" - coordinates, diameter, color
 * "pl 0.0,1.0,2.0  |  1.0,0.0,0.0 | 255,0,255" - coordinates, 3d normalized vector, color
 * "sq 0.0,0.0,20.6 | 1.0,0.0,0.0 | 12.6 | 255,0,255" - coordinates of center square, 3d norm vector, side size, color
 * "cy 50.0,0.0,20.6 | 0.0,0.0,1.0 | 10,0,255 | 14.2 | 21.42" - xyz coor | 3d norm vector | cylinder diameter | height | color
 * "tr 10.0,20.0,10.0 | 10.0,10.0,20.0 | 20.0,10.0,10.0 | 0,0,255" - xyz first point | xyz s_point | xyz th_point | color
 *
 * Функции под листы в отдельном каталоге - готово
 * Функции для создания каждой фигуры в отдельном каталоге -
 * Навести порядок в заголовочных -
 *
 * каждую строку проверить не спец - внести в символ - вызвать фунцию обработки параметра
 */

void 	parser(char *str, s_scene *scene)
{
	const unsigned char spec = check_specif(str);

	if (str[0] == 'A')
	{
		//work with amb
	}
	else
	{
		//work with spec and str
	}
}

//char 		check_specif(char *str)
//{
//	unsigned char	spec;
//
//	spec |= S_NUL;
//	if (str[0] == 'R')
//		spec |= S_R;
//	else if (str[0] == 'c')
//		spec |= S_CM;
//	else if (str[0] == 'l')
//		spec |= S_LT;
//	else if ()
//	return (spec);
//}