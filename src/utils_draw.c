/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:09:36 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/08 15:35:15 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	draw_wall_floor(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map_two_d[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->wall, x
					* SIZE, y * SIZE);
			else if (data->map_two_d[y][x] == '0'
				|| data->map_two_d[y][x] == 'P' || data->map_two_d[y][x] == 'C'
				|| data->map_two_d[y][x] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->floor, x
					* SIZE, y * SIZE);
			x++;
		}
		y++;
	}
	return (0);
}

int	draw_others(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map_two_d[y][x] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->collectible,
					x * SIZE, y * SIZE);
			else if (data->map_two_d[y][x] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->exit, x
					* SIZE, y * SIZE);
			x++;
		}
		y++;
	}
	return (0);
}

int	draw_player(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->actor,
		data->player.pos_x * SIZE, data->player.pos_y * SIZE);
	return (0);
}

int	draw_all_map(t_data *data)
{
	draw_wall_floor(data);
	draw_others(data);
	draw_player(data);
	draw_win(data);
	return (0);
}

int	move_player(t_data *data)
{
	if (data->won == 1)
		return (0);
	if (data->map_two_d[data->player.pos_y][data->player.pos_x] == 'C')
	{
		data->map_two_d[data->player.pos_y][data->player.pos_x] = '0';
		data->collectible_collected++;
		if (data->collectible_collected == data->collectible_count)
			data->exit_unlocked = 1;
	}
	else if (data->map_two_d[data->player.pos_y][data->player.pos_x] == 'E')
	{
		if (data->exit_unlocked == 1)
		{
			data->map_two_d[data->player.pos_y][data->player.pos_x] = '0';
			data->won = 1;
		}
		else
		{
			printf("Collect all objects first\n");
			return (0);
		}
	}
	printmove(data);
	draw_all_map(data);
	return (0);
}
