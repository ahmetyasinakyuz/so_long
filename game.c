/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakyuz <aakyuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:14:20 by aakyuz            #+#    #+#             */
/*   Updated: 2024/12/16 15:58:44 by aakyuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_so_long *sl)
{
	if (keycode == 65307)
	{
		ft_printf("You lost! Moves: %d\n", sl->moves);
		destroy_window(sl);
		exit(0);
	}
	else if ((keycode == 119 && move_player(sl, 0, -1) == 1) || (keycode == 97
			&& move_player(sl, -1, 0) == 1) || (keycode == 115
			&& move_player(sl, 0, 1) == 1) || (keycode == 100 && move_player(sl,
				1, 0) == 1))
	{
		sl->moves++;
		ft_printf("moves: %d\n", sl->moves);
	}
	return (0);
}

void	found_exit(t_so_long *sl)
{
	int	i;
	int	j;

	i = 0;
	while (i < sl->map_size_y)
	{
		j = 0;
		while (j < sl->map_size_x - 1)
		{
			if (sl->map[i][j] == 'E')
			{
				sl->exit.x = j;
				sl->exit.y = i;
				return ;
			}
			j++;
		}
		i++;
	}
	exit(0);
}

void	game(t_so_long *sl)
{
	found_exit(sl);
	sl->mlx = mlx_init();
	sl->win = mlx_new_window(sl->mlx, ((sl->map_size_x - 1) * 48),
			((sl->map_size_y) * 48), "aakyuz's so_long");
	sl->moves = 0;
	load_images(sl);
	draw_map(sl);
	mlx_hook(sl->win, 2, 1L << 0, key_press, sl);
	mlx_hook(sl->win, 17, 1L << 17, destroy_window, sl);
	mlx_loop(sl->mlx);
}
