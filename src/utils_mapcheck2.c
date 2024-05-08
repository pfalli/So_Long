/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mapcheck2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:59:54 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/08 18:01:46 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	allocate_visited(t_data *data)
{
	int	i;
	int	j;

	data->visited = malloc(sizeof(int *) * data->map.height);
	i = 0;
	while (i < data->map.height)
	{
		data->visited[i] = malloc(sizeof(int) * data->map.width);
		j = 0;
		while (j < data->map.width)
		{
			data->visited[i][j] = 0;
			j++;
		}
		i++;
	}
	is_exit_accessible(data, data->player.pos_x, data->player.pos_y);
	if (data->exit_accessible == 0)
	{
		printf("Exit is not accessible from the current position.\n");
		exit(EXIT_FAILURE);
	}
	free_visited(data);
	return (0);
}

int	access_collectible(t_data *data)
{
	if (data->collectible_count != data->collectible_accessible)
	{
		printf("All collectible are not accessible.\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	wrong_elements(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	{
		while (y < data->map.height)
		{
			x = 0;
			while (x < data->map.width - 1)
			{
				if (data->map_two_d[y][x] != 'C' && data->map_two_d[y][x] != 'P'
					&& data->map_two_d[y][x] != '0'
					&& data->map_two_d[y][x] != '1'
					&& data->map_two_d[y][x] != 'E')
				{
					printf("data->map.width: %d\n", data->map.width - 1);
					printf("data->map.height: %d\n", data->map.height);
					printf("Wrong elements in Map\n");
					exit(EXIT_FAILURE);
				}
				x++;
			}
			y++;
		}
	}
	return (0);
}

int	check_map_errors(t_data *data)
{
	int	y;

	y = 0;
	//	wrong_elements(data);
	closed_by_walls(data);
	only_1_exit(data);
	only_1_player(data);
	atleast_1_collectible(data);
	allocate_visited(data);
	access_collectible(data);
	//	while (y < data->map.height - 1)
	//	{
	//		if (ft_strlen_solong(data->map_two_d[y]) != data->map.width)
	//		{
	//			printf("Map not rectangular\n");
	//			exit(EXIT_FAILURE);
	//		}
	//		y++;
	//	}
	return (0);
}
