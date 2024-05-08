/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mapcheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:23:03 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/08 12:00:36 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	closed_by_walls(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (x < data->map.width)
	{
		if (data->map_two_d[0][x] != '1' || data->map_two_d[data->map.height
			- 1][x] != '1')
		{
			printf("Map not closed by walls\n");
			exit(EXIT_FAILURE);
		}
		x++;
	}
	while (y < data->map.height)
	{
		if (data->map_two_d[y][0] != '1' || data->map_two_d[y][data->map.width
			- 1] != '1')
		{
			printf("Map not closed by walls\n");
			exit(EXIT_FAILURE);
		}
		y++;
	}
}

void	only_1_exit(t_data *data)
{
	int	y;
	int	flag;
	int	x;

	y = 0;
	flag = 0;
	{
		while (y < data->map.height)
		{
			x = 0;
			while (x < data->map.width)
			{
				if (data->map_two_d[y][x] == 'E')
					flag++;
				x++;
			}
			y++;
		}
		if (flag > 1)
			exit(EXIT_FAILURE);
		if (flag == 0)
			exit(EXIT_FAILURE);
	}
}

void	only_1_player(t_data *data)
{
	int	y;
	int	flag;
	int	x;

	y = 0;
	flag = 0;
	{
		while (y < data->map.height)
		{
			x = 0;
			while (x < data->map.width)
			{
				if (data->map_two_d[y][x] == 'P')
					flag++;
				x++;
			}
			y++;
		}
		if (flag > 1)
			exit(EXIT_FAILURE);
		if (flag == 0)
			exit(EXIT_FAILURE);
	}
}

int	atleast_1_collectible(t_data *data)
{
	int	y;
	int	x;

	data->collectible_accessible = 0;
	y = 0;
	{
		while (y < data->map.height)
		{
			x = 0;
			while (x < data->map.width)
			{
				if (data->map_two_d[y][x] == 'C')
					data->collectible_count++;
				x++;
			}
			y++;
		}
		if (data->collectible_count == 0)
		{
			printf("No Collectibles\n");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

void	is_exit_accessible(t_data *data, int x, int y)
{
	if (data->map_two_d[y][x] == '1' || y < 0 || x < 0 || x >= data->map.width
		|| y >= data->map.height)
		return ;
	if (data->visited[y][x])
		return ;
	data->visited[y][x] = 1;
	if (data->map_two_d[y][x] == 'E')
		data->exit_accessible = 1;
	if (data->map_two_d[y][x] == 'C')
		data->collectible_accessible++;
	is_exit_accessible(data, x - 1, y);
	is_exit_accessible(data, x + 1, y);
	is_exit_accessible(data, x, y - 1);
	is_exit_accessible(data, x, y + 1);
	return ;
}
