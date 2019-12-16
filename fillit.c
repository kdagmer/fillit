/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdagmer <kdagmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:30:35 by kdagmer           #+#    #+#             */
/*   Updated: 2019/12/16 14:03:36 by kdagmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			print_map(t_tetris *tetris);

/*static int		removelast(t_tetris *tetris, t_piece *tet)
{
	return (0);
}*/

static int		addtomap(t_tetris *tetris, t_piece *tet)
{
	int y;
	int x;
	int ok;

	y = 0;
	ok = 0;
	printf("h: %d\n", tet->height);
	printf("w: %d\n", tet->width);
	while (y < tet->height)
	{
		x = 0;
		while (x < tet->width)
		{
			printf("x: %d\n", x);
			printf("y: %d\n", y);
			if (tetris->map[y][x] == TEMPTY && tet->map[y][x] != TEMPTY)
			{
				tetris->map[y][x] = tet->map[y][x];
				print_map(tetris);
				ok = 1;
			}
			else if (tetris->map[y][x] != TEMPTY)
			{
				ok = 0;
			}
			x++;
		}
		y++;
	}
	if (ok == 1)
		return (1);
	return (0);
}

/*
									  solver (if placer 0 : size++)
										|
										placer (if addtomap 1 : placer)
										/
								addtomap
								/		\
			if 1 : placer next tet		if 0 : removelast
*/

static int		placer(t_tetris *tetris, t_piece *tet)
{
	tet->y = 0;
	tet->x = 0;
	printf("htet: %d\n", tet->height);
	printf("wtet: %d\n", tet->width);
	while (tet->y + tet->height <= tetris->size)
	{
		tet->x = 0;
		while (tet->x + tet->width <= tetris->size)
		{
			if (addtomap(tetris, tet))
				if (placer(tetris, tet->next))
					return (1);
			tet->x++;
		}
		tet->y++;
	}
	return (0);
}

void			solver(t_tetris *tetris)
{
	while (!placer(tetris, tetris->pieces))
	{
		tetris->size++;
		printf("tetsize: %d\n", tetris->size);
		print_map(tetris);
	}
}

void			print_map(t_tetris *tetris)
{
	int y;
	int x;

	y = 0;
	while (y < tetris->size)
	{
		x = 0;
		while (x < tetris->size)
			ft_putchar(tetris->map[y][x++]);
		ft_putchar('\n');
		y++;
	}
}

int				main(int ac, char **av)
{
	t_tetris tetris;
	t_piece *temp;
	int i;

	if (ac != 2)
	{
		print_error(2);
		return (0);
	}
	if (tet_create(&tetris, av[1]))
	{
		solver(&tetris);
		printf("\n\n\n--------print map--------\n\n\n");
		print_map(&tetris);
		printf("\n\n\n");
		/*printf("%s\n", tetris.pieces->map[0]);
		printf("%s\n", tetris.pieces->next->map[0]);
		printf("%s\n", tetris.pieces->next->map[1]);
		printf("%s\n", tetris.pieces->next->map[2]);
		printf("%s\n", tetris.pieces->next->next->map[0]);
		printf("%s\n", tetris.pieces->next->next->map[1]);
		printf("%s\n", tetris.pieces->next->next->next->map[0]);
		printf("%s\n", tetris.pieces->next->next->next->map[1]);
		printf("%s\n", tetris.pieces->next->next->next->next->map[0]);
		printf("%s\n", tetris.pieces->next->next->next->next->map[1]);
		printf("---------\n");*/
		temp = tetris.pieces;
		while (temp)
		{
			i = 0;
			while (temp->map[i] != NULL)
			{
				printf("%d %s\n", i, temp->map[i]);
				i++;
			}
			temp = temp->next;
		}
	}
	else
		print_error(1);
	return (1);
}
