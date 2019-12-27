/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdagmer <kdagmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:30:35 by kdagmer           #+#    #+#             */
/*   Updated: 2019/12/27 14:15:19 by kdagmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		removetomap(t_tetris *tetris, t_piece *tet)
{
	int		x;
	int		y;

	y = 0;
	while (y < tet->height)
	{
		x = 0;
		while (x < tet->width)
		{
			if (tet->map[y][x] != TEMPTY)
				tetris->map[y + tet->y][x + tet->x] = TEMPTY;
			x++;
		}
		y++;
	}
}

static int		addtomap(t_tetris *tetris, t_piece *tet, int y, int x)
{
	while (y < tet->height)
	{
		x = 0;
		while (x < tet->width)
		{
			if (tetris->map[y + tet->y][x + tet->x] != TEMPTY &&\
					tet->map[y][x] != TEMPTY)
				return (0);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < tet->height)
	{
		x = 0;
		while (x < tet->width)
		{
			if (tet->map[y][x] != TEMPTY)
				tetris->map[y + tet->y][x + tet->x] = tet->map[y][x];
			x++;
		}
		y++;
	}
	return (1);
}

static int		placer(t_tetris *tetris, t_piece *tet)
{
	if (!tet)
		return (1);
	tet->y = 0;
	tet->x = 0;
	while (tet->y + tet->height <= tetris->size)
	{
		tet->x = 0;
		while (tet->x + tet->width <= tetris->size)
		{
			if (addtomap(tetris, tet, 0, 0))
			{
				if (placer(tetris, tet->next) == 1)
					return (1);
				else
					removetomap(tetris, tet);
			}
			tet->x++;
		}
		tet->y++;
	}
	if (tet->letter == 'A')
		return (3);
	return (0);
}

void			solver(t_tetris *tetris)
{
	int i;

	while (placer(tetris, tetris->pieces) == 3)
	{
		tetris->size++;
		i = 0;
		while (i < tetris->size)
			ft_memset(tetris->map[i++], TEMPTY, tetris->size);
	}
}

int				main(int ac, char **av)
{
	t_tetris tetris;

	if (ac != 2)
	{
		print_error(2);
		return (0);
	}
	if (tet_create(&tetris, av[1]))
	{
		solver(&tetris);
		print_map(&tetris);
		free_map(&tetris);
	}
	else
		print_error(1);
	return (1);
}
