/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mapcheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:23:03 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/23 09:57:14 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void closed_by_walls(t_data *data)
{
    int y;
    int x;

    y = 0;
    x = 0;
    // Check the top row
    while (x < data->map.width)
    {
        if (data->map_two_d[0][x] != '1')
        {
            printf("Top row not closed at column %d\n", x);
            printf("Character found: %c\n", data->map_two_d[0][x]);
            printf("Map not closed by walls horizontal\n");
            exit(EXIT_FAILURE);
        }
        x++;
    }
    // Check the bottom row
    x = 0;
    while (x < data->map.width)
    {
        if (data->map_two_d[data->map.height - 1][x] != '1')
        {
            printf("Bottom row not closed at column %d\n", x);
            printf("Character found: %c\n", data->map_two_d[data->map.height - 1][x]);
            printf("Map not closed by walls horizontal\n");
            exit(EXIT_FAILURE);
        }
        x++;
    }
    // Check the left and right columns
    while (y < data->map.height)
    {
        if (data->map_two_d[y][0] != '1')
        {
            printf("Left column not closed at row %d\n", y);
            printf("Character found: %c\n", data->map_two_d[y][0]);
            printf("Map not closed by wall vertical\n");
            exit(EXIT_FAILURE);
        }
        if (data->map_two_d[y][data->map.width - 1] != '1')
        {
            printf("Right column not closed at row %d\n", y);
            printf("Character found: %c\n", data->map_two_d[y][data->map.width - 1]);
            printf("Map not closed by wall vertical\n");
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
		if (flag != 1)
		{
			printf("Should be only one Exit!\n");
			exit(EXIT_FAILURE);
		}
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
		if (flag != 1)
		{
			printf("Should be only 1 Player!\n");
			exit(EXIT_FAILURE);
		}
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
// MAP CHECKER
void	is_exit_accessible(t_data *data, int x, int y)
{
	if (data->map_two_d[y][x] == '1' || y < 0 || x < 0 || x >= data->map.width
		|| y >= data->map.height)
		return ;
	if (data->visited[y][x])
		return ;
	data->visited[y][x] = 1;
	if (data->map_two_d[y][x] == 'E')
	{
		data->exit_accessible = 1;
		if (data->collectible_count != data->collectible_accessible)
		{
			printf("All collectible are not accessible.\n");
			exit(EXIT_FAILURE);
		}
	}
	if (data->map_two_d[y][x] == 'C')
		data->collectible_accessible++;
	is_exit_accessible(data, x - 1, y);
	is_exit_accessible(data, x + 1, y);
	is_exit_accessible(data, x, y - 1);
	is_exit_accessible(data, x, y + 1);
	return ;
}
