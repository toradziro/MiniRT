/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killed_by_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:36:35 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:41:23 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"
#include <stdio.h>

void killed_by_error(int num)
{
    if (num == MALLOC_ERROR)
    {
        printf("Error: malloc error.\n");
    }
    else if (num == INV_AM_OF_ARG)
    {
        printf("Error: invalid amount of the arguments.\n");
    }
    else if (num == INV_FILE_NAME)
    {
        printf("Error: invalid file name.\n");
    }
    else if (num == INV_COLOR)
    {
        printf("Error: invalid color.\n");
    }
    else if (num == UNKNWN_ARG)
    {
        printf("Error: unknown argument.\n");
    }
    else if (num == NOT_ENOUGH)
    {
        printf("Error: NOT ENOUGH ARGUMENTS, JUST FIX FILE, DON'T TOUCH MY PARSER!\n");
    }
    exit(1);
}

void check_valid_name(char* str)
{
    int i;

    i = 0;
    while (str[i] == '.')
    {
        ++i;
    }
    while (((str[i] >= 32 && str[i] < 127)) && str[i] != '.' && str[i])
    {
        ++i;
    }
    if (str[i] != '.')
    {
        killed_by_error(INV_FILE_NAME);
    }
    ++i;
    if (str[i] != 'r' || str[i + 1] != 't')
    {
        killed_by_error(INV_FILE_NAME);
    }
}
