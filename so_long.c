/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakyuz <aakyuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:33:04 by aakyuz            #+#    #+#             */
/*   Updated: 2024/12/16 15:59:43 by aakyuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	file_type(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 1] != 'r' || file[i - 2] != 'e' || file[i - 3] != 'b' || file[i
			- 4] != '.')
	{
		ft_printf("Error! File must be .ber\n");
		exit(1);
	}
}

int	main(int argc, char *argv[])
{
	int	fd1;
	int	fd2;

	if (argc != 2)
	{
		ft_printf("Error! Must be 2 arguments\n");
		exit(1);
	}
	file_type(argv[1]);
	fd1 = open(argv[1], O_RDWR);
	fd2 = open(argv[1], O_RDWR);
	if (fd1 == -1 || fd2 == -1)
	{
		ft_printf("Error! File didn't open\n");
		exit(1);
	}
	map(fd1, fd2);
}
