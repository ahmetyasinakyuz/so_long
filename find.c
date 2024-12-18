/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakyuz <aakyuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:02:43 by aakyuz            #+#    #+#             */
/*   Updated: 2024/12/15 20:50:22 by aakyuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(t_so_long *sl, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < sl->map_size_y - 1)
	{
		j = 0;
		while (j < sl->map_size_x - 1)
		{
			if (map[i][j] == 'P')
			{
				sl->player.x = j;
				sl->player.y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	find_exit(t_so_long *sl, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < sl->map_size_y)
	{
		j = 0;
		while (j < sl->map_size_x - 1)
		{
			if (map[i][j] == 'E')
			{
				sl->exit.x = j;
				sl->exit.y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	find_collect(t_so_long *sl, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (sl->map_size_y - 1 > i)
	{
		j = 0;
		while (sl->map_size_x - 1 > j)
		{
			if (map[i][j] == 'C')
			{
				sl->collect.x = j;
				sl->collect.y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}
