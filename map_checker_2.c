/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakyuz <aakyuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:52:06 by aakyuz            #+#    #+#             */
/*   Updated: 2024/12/16 16:02:57 by aakyuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_arg_map(char **map)
{
	int	i;
	int	j;
	int	p;
	int	e;
	int	c;

	i = -1;
	p = 0;
	e = 0;
	c = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'P')
				p++;
			if (map[i][j] == 'E')
				e++;
			if (map[i][j] == 'C')
				c++;
		}
	}
	if (p != 1 || e != 1 || c < 1)
		map_error(map, "Error\nİnvalid items in map");
}

void	map_size_y(int fd, t_so_long *sl)
{
	int		i;
	char	*line;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
		i++;
	}
	sl->map_size_y = i;
}

void	fill(char **map, int player_x, int player_y, t_so_long *sl)
{
	if (player_x < 0 || player_x >= sl->map_size_x || player_y < 0
		|| player_y >= sl->map_size_y || map[player_y][player_x] == '1'
		|| map[player_y][player_x] == '*')
	{
		return ;
	}
	map[player_y][player_x] = '*';
	fill(map, player_x + 1, player_y, sl);
	fill(map, player_x - 1, player_y, sl);
	fill(map, player_x, player_y + 1, sl);
	fill(map, player_x, player_y - 1, sl);
}

void	map_wall(t_so_long *sl, char **map)
{
	int	i;

	sl->map = (char **)malloc(sizeof(char *) * (sl->map_size_y + 1));
	if (!sl->map)
		map_error(map, "Error\nMalloc failed");
	i = -1;
	while (map[++i])
	{
		sl->map[i] = strdup(map[i]);
		if (!sl->map[i])
			map_error(map, "Error\nMalloc failed");
	}
	sl->map[i] = NULL;
	find_player(sl, map);
	fill(map, sl->player.x, sl->player.y, sl);
	find_exit(sl, map);
	find_collect(sl, map);
	if (sl->collect.x != 0 || sl->collect.y != 0 || sl->exit.x != 0
		|| sl->exit.y != 0)
	{
		while (sl->map_size_y--)
			free(sl->map[sl->map_size_y]);
		free(sl->map);
		map_error(map, "Error\nNo path to exit or collectible");
	}
}

void	map_error(char **map, char *error_message)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	ft_printf("%s\n", error_message);
	exit(1);
}
