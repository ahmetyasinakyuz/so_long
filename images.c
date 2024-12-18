/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakyuz <aakyuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:41:15 by aakyuz            #+#    #+#             */
/*   Updated: 2024/12/16 13:14:01 by aakyuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_so_long *sl)
{
	int	img_width;
	int	img_height;

	sl->img_wall = mlx_xpm_file_to_image(sl->mlx, "./textures/wall.xpm",
			&img_width, &img_height);
	sl->img_player = mlx_xpm_file_to_image(sl->mlx, "./textures/player.xpm",
			&img_width, &img_height);
	sl->img_collectible = mlx_xpm_file_to_image(sl->mlx, "./textures/coin.xpm",
			&img_width, &img_height);
	sl->img_exit = mlx_xpm_file_to_image(sl->mlx, "./textures/exit.xpm",
			&img_width, &img_height);
	sl->img_empty = mlx_xpm_file_to_image(sl->mlx, "./textures/empty.xpm",
			&img_width, &img_height);
}

void	draw_map(t_so_long *sl)
{
	sl->map_coord.y = -1;
	while (++sl->map_coord.y < sl->map_size_y)
	{
		sl->map_coord.x = -1;
		while (++sl->map_coord.x < sl->map_size_x - 1)
		{
			if (sl->map[sl->map_coord.y][sl->map_coord.x] == '1')
				mlx_put_image_to_window(sl->mlx, sl->win, sl->img_wall,
					sl->map_coord.x * 48, sl->map_coord.y * 48);
			else if (sl->map[sl->map_coord.y][sl->map_coord.x] == 'P')
				mlx_put_image_to_window(sl->mlx, sl->win, sl->img_player,
					sl->map_coord.x * 48, sl->map_coord.y * 48);
			else if (sl->map[sl->map_coord.y][sl->map_coord.x] == 'C')
				mlx_put_image_to_window(sl->mlx, sl->win, sl->img_collectible,
					sl->map_coord.x * 48, sl->map_coord.y * 48);
			else if (sl->map[sl->map_coord.y][sl->map_coord.x] == 'E')
				mlx_put_image_to_window(sl->mlx, sl->win, sl->img_exit,
					sl->map_coord.x * 48, sl->map_coord.y * 48);
			else
				mlx_put_image_to_window(sl->mlx, sl->win, sl->img_empty,
					sl->map_coord.x * 48, sl->map_coord.y * 48);
		}
	}
}

int	all_collectibles_collected(t_so_long *sl)
{
	int	i;
	int	j;

	i = 0;
	while (i < sl->map_size_y)
	{
		j = 0;
		while (j < sl->map_size_x - 1)
		{
			if (sl->map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	destroy_window(t_so_long *sl)
{
	int	i;

	i = 0;
	while (i < sl->map_size_y)
	{
		free(sl->map[i]);
		i++;
	}
	free(sl->map);
	mlx_destroy_image(sl->mlx, sl->img_collectible);
	mlx_destroy_image(sl->mlx, sl->img_empty);
	mlx_destroy_image(sl->mlx, sl->img_exit);
	mlx_destroy_image(sl->mlx, sl->img_player);
	mlx_destroy_image(sl->mlx, sl->img_wall);
	mlx_destroy_window(sl->mlx, sl->win);
	mlx_destroy_display(sl->mlx);
	free(sl->mlx);
	exit(0);
}

int	move_player(t_so_long *sl, int dx, int dy)
{
	int	x;
	int	y;

	x = sl->player.x + dx;
	y = sl->player.y + dy;
	if (x >= 0 && x < sl->map_size_x && y >= 0 && y < sl->map_size_y
		&& sl->map[y][x] != '1')
	{
		if ((all_collectibles_collected(sl) == 1 && sl->map[y][x] == 'E'))
		{
			ft_printf("You won! Moves: %d\n", sl->moves);
			destroy_window(sl);
		}
		if (sl->player.x == sl->exit.x && sl->player.y == sl->exit.y)
			sl->map[sl->player.y][sl->player.x] = 'E';
		else
			sl->map[sl->player.y][sl->player.x] = '0';
		sl->player.x = x;
		sl->player.y = y;
		sl->map[sl->player.y][sl->player.x] = 'P';
		draw_map(sl);
		return (1);
	}
	return (0);
}
