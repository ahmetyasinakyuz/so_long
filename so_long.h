/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakyuz <aakyuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:33:00 by aakyuz            #+#    #+#             */
/*   Updated: 2024/12/16 15:30:25 by aakyuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./ft_printf/ft_printf.h"
# include "./minilibx-linux/mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <string.h>

typedef struct s_coord
{
	int		x;
	int		y;
}			t_coord;

typedef struct s_so_long
{
	int		map_size_x;
	int		map_size_y;
	int		moves;
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_player;
	void	*img_collectible;
	void	*img_exit;
	void	*img_empty;
	char	**map;
	t_coord	player;
	t_coord	exit;
	t_coord	collect;
	t_coord	map_coord;
}			t_so_long;

int			destroy_window(t_so_long *sl);
void		map_error(char **map, char *str);
void		load_images(t_so_long *sl);
void		draw_map(t_so_long *sl);
void		check_arg_map(char **map);
void		map(int fd1, int fd2);
void		map_size_y(int fd, t_so_long *sl);
void		map_wall(t_so_long *sl, char **map);
void		find_player(t_so_long *sl, char **map);
void		find_exit(t_so_long *sl, char **map);
void		find_collect(t_so_long *sl, char **map);
void		map_wall(t_so_long *sl, char **map);
void		game(t_so_long *sl);
int			move_player(t_so_long *sl, int dx, int dy);

#endif