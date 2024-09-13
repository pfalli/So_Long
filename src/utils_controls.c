/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:26:06 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/08 16:09:57 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	printf("EXIT\n");
	free_map(data);
	free_images(data);
	free_mlx(data);
	exit(0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data);
	if (keycode == A)
		data->player.pos_x -= 1;
	else if (keycode == W)
		data->player.pos_y -= 1;
	else if (keycode == D)
		data->player.pos_x += 1;
	else if (keycode == S)
		data->player.pos_y += 1;
	if (data->map_two_d[data->player.pos_y][data->player.pos_x] == '1')
	{
		if (keycode == A)
			data->player.pos_x += 1;
		if (keycode == W)
			data->player.pos_y += 1;
		if (keycode == D)
			data->player.pos_x -= 1;
		if (keycode == S)
			data->player.pos_y -= 1;
		return (0);
	}
	if (keycode == A || keycode == W || keycode == S || keycode == D)
		move_player (data);
	return (0);
}
