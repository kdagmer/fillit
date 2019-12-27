/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tet_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdagmer <kdagmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:44:28 by kdagmer           #+#    #+#             */
/*   Updated: 2019/12/27 13:47:13 by kdagmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			free_map(t_tetris *tetris)
{
	int		i;
	t_piece	*temp;

	i = 0;
	if (tetris->map)
	{
		while (i < 4 * tetris->nb_pieces)
			ft_memdel((void **)&tetris->map[i++]);
		ft_memdel((void **)&tetris->map);
	}
	while (!(tetris->pieces == NULL))
	{
		i = 0;
		temp = tetris->pieces->next;
		while (i < tetris->pieces->height + 1)
			ft_memdel((void **)&tetris->pieces->map[i++]);
		ft_memdel((void **)&tetris->pieces->map);
		ft_memdel((void **)&tetris->pieces);
		tetris->pieces = temp;
	}
}

void			print_map(t_tetris *tetris)
{
	int	y;
	int	x;

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

static int		map(t_tetris *tetris, int size)
{
	int i;

	if (!(tetris->map = (char **)malloc(size * sizeof(char *))))
		return (0);
	i = 0;
	while (i < size)
	{
		if (!(tetris->map[i] = (char *)malloc(size * sizeof(char))))
			return (0);
		ft_memset(tetris->map[i], TEMPTY, size);
		i++;
	}
	return (1);
}

int				tet_create(t_tetris *tetris, char *file)
{
	int sd;

	sd = 1;
	tetris->pieces = NULL;
	tetris->map = NULL;
	tetris->nb_pieces = 0;
	if (check_file(tetris, file))
	{
		map(tetris, 4 * tetris->nb_pieces);
		while (sd * sd < 4 * tetris->nb_pieces)
			sd++;
		tetris->size = sd;
		return (1);
	}
	return (0);
}
