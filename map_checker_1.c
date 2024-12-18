/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakyuz <aakyuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:30:42 by aakyuz            #+#    #+#             */
/*   Updated: 2024/12/16 15:12:51 by aakyuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_char(char **map, t_so_long *sl)
{
	int	i;
	int	j;

	i = 0;
	while (sl->map_size_y - 1 > i)
	{
		j = 0;
		while (sl->map_size_x - 1 > j)
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'P'
				&& map[i][j] != 'E' && map[i][j] != 'C')
				map_error(map, "Error\nInvalid character in map");
			j++;
		}
		i++;
	}
}

void	check_rectangle(char **map, t_so_long *sl)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (map[0][i])
		i++;
	len = i;
	sl->map_size_x = len;
	i = 0;
	while (sl->map_size_y > i)
	{
		j = 0;
		while (map[i][j])
			j++;
		if (i == sl->map_size_y - 1 && j != len - 1)
			map_error(map, "Error\nMap isn't rectangle");
		else if (i != sl->map_size_y - 1 && j != len)
			map_error(map, "Error\nMap isn't rectangle");
		i++;
	}
}

void	check_wall(char **map, t_so_long *sl)
{
	int	i;

	i = 0;
	while (sl->map_size_x - 1 > i)
	{
		if (map[0][i] != '1')
			map_error(map, "Error\nThere's a hole in the wall");
		i++;
	}
	i = 0;
	while (map[sl->map_size_y - 1][i])
	{
		if (map[sl->map_size_y - 1][i] != '1')
			map_error(map, "Error\nThere's a hole in the wall");
		i++;
	}
	i = 1;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][sl->map_size_x - 2] != '1')
			map_error(map, "Error\nThere's a hole in the wall");
		i++;
	}
}

void	init_sl(t_so_long *sl)
{
	sl->map_size_x = 0;
	sl->map_size_y = 0;
	sl->moves = 0;
	sl->player.x = 0;
	sl->player.y = 0;
	sl->exit.x = 0;
	sl->exit.y = 0;
	sl->collect.x = 0;
	sl->collect.y = 0;
	sl->map_coord.x = 0;
	sl->map_coord.y = 0;
	sl->map = NULL;
}

void	map(int fd1, int fd2)
{
	int			i;
	char		**map;
	t_so_long	sl;

	init_sl(&sl);
	map_size_y(fd1, &sl);
	map = malloc(sizeof(char *) * (sl.map_size_y + 1));
	i = 0;
	while (1)
	{
		map[i] = get_next_line(fd2);
		if (map[i] == NULL)
			break ;
		i++;
	}
	check_rectangle(map, &sl);
	check_char(map, &sl);
	check_arg_map(map);
	check_wall(map, &sl);
	map_wall(&sl, map);
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	game(&sl);
}
