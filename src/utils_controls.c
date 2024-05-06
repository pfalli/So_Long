/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:26:06 by pfalli            #+#    #+#             */
/*   Updated: 2024/04/27 16:26:06 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    printf("EXIT");
    exit(0);
}

int key_press(int keycode, t_data *data) // TOO LONG
{
    if (keycode == ESC)
		close_window(data);
	if (keycode == A)
		data->player.pos_x -= 1;
        if (data->map_twoD[data->player.pos_y][data->player.pos_x] == '1')
        {
            data->player.pos_x += 1;
            return( 0);
        }
	else if ( keycode == W)
		data->player.pos_y -= 1;
        if (data->map_twoD[data->player.pos_y][data->player.pos_x] == '1')
        {
            data->player.pos_y += 1;
            return( 0);
        }
	else if (keycode == D)
		data->player.pos_x += 1;
        if (data->map_twoD[data->player.pos_y][data->player.pos_x] == '1')
        {
            data->player.pos_x -= 1;
            return( 0);
        }
	else if (keycode == S )
		data->player.pos_y += 1;
        if (data->map_twoD[data->player.pos_y][data->player.pos_x] == '1')
        {
            data->player.pos_y -= 1;
            return( 0);
        }
    printf("Moves = %d\n", data->moves);
    move_player(data);
	return(0);
}