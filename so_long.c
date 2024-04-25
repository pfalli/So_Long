/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:21:35 by pfalli            #+#    #+#             */
/*   Updated: 2024/04/12 13:21:35 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    printf("EXIT\n");
    exit(0);
}

int load_textures(t_texture *texture, t_data *data) // function for textures
{
	int x, j;

	texture->floor = mlx_xpm_file_to_image(data->mlx, "textures/floor.xpm", &x, &j);
	texture->wall = mlx_xpm_file_to_image(data->mlx, "textures/wall.xpm", &x, &j);
	texture->collectible = mlx_xpm_file_to_image(data->mlx, "textures/pinky.xpm", &x, &j);
	texture->exit = mlx_xpm_file_to_image(data->mlx, "textures/exit.xpm", &x, &j);
	texture->player = mlx_xpm_file_to_image(data->mlx, "textures/wizard.xpm", &x, &j);
	return(0);
}

int draw_wall_floor(t_texture *texture, t_data *data) // after \n there is \r
{
	int fd = open("map/valid.ber", O_RDONLY);
	int x = 0;
	int y = 0;
	int status;
	char c;

	while ((status = read(fd, &c, 1)) > 0) 
	{
		if (c == '1') 
		{
			mlx_put_image_to_window(data->mlx, data->win, texture->wall, x, y);
			x += SIZE;
		}
		else if ( c == '\n')
		{
			y += SIZE;
			x = 0;
		}
		else if (c != '\r')
		{
			mlx_put_image_to_window(data->mlx, data->win, texture->floor, x, y);
			x += SIZE;
		}
	}
	close (fd);
	mlx_destroy_image(data->mlx, texture->wall);
	mlx_destroy_image(data->mlx, texture->floor);
	return(0);
}


int draw_all_map(t_texture *texture, t_data *data, t_player *player)
{
	draw_wall_floor(texture, data);
	int fd = open("map/valid.ber", O_RDONLY);
	int x = 0;
	int y = 0;
	int status;
	char c;

	while ((status = read(fd, &c, 1)) > 0) 
	{
		if ( c == '\n')
		{
			y += SIZE;
			x = 0;
		}
		else if (c == 'C')
		{
        	mlx_put_image_to_window(data->mlx, data->win, texture->collectible, x, y);
			x += SIZE;
		}
		else if (c == 'E')
		{
        	mlx_put_image_to_window(data->mlx, data->win, texture->exit, x, y);
			x += SIZE;
		}
		else if (c == 'P')
		{
			if (!player->is_initialized) {
        		player->pos_y = y;
        		player->pos_x = x;
        		player->is_initialized = true;
				x += SIZE;
			}
			mlx_put_image_to_window(data->mlx, data->win, texture->player, player->pos_x, player->pos_y);
			player->pos_x += SIZE;
		}
		else if ( c != '\r' ||  c != '0' ||  c != '1')
			x += SIZE;
	}
	if (status == -1)
    {
        perror("Error reading file");
        return (1);
    }
	close (fd);
	return(0);
	
}


int key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data);
	if (keycode == A)
		data->player.pos_x -= SIZE;
	else if ( keycode == W)
		data->player.pos_y -= SIZE;
	else if (keycode == D)
		data->player.pos_x += SIZE;
	else if (keycode == S )
		data->player.pos_y += SIZE;
	printf("player pos x: %d and player pos y: %d\n", data->player.pos_x, data->player.pos_y);
	mlx_clear_window(data->mlx, data->win);
	draw_all_map(&data->texture, data, &data->player);
	return(0);
}


//	void	init_game(t_data data)
//	{
//		data.won = 0;
//		data.player.is_initialized = 0;
//	}

//--------------------------------------------------------------------------------------------------------------------------------------//

//	int store_start_pos_player(t_data *data)
//	{
//		int fd = open("map/valid.ber", O_RDONLY);
//		int x = 0;
//		int y = 0;
//		int status;
//		char c;
//	
//		while ((status = read(fd, &c, 1)) > 0) 
//		{
//			if (c == 'P') 
//			{
//				data->player.pos_x = x;
//				data->player.pos_y = y;
//			}
//			else if ( c == '\n')
//			{
//				y += SIZE;
//				x = 0;
//			}
//		close (fd);
//		}
//	}
//	
//	int draw_player(t_data *data)
//	{
//		
//	}




int main(void)
{
	t_data data;
	t_texture texture;
	t_player player;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_SIZE_X, WIN_SIZE_Y, "Sotomayor");
	//data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	load_textures(&texture, &data);
	draw_all_map(&texture, &data, &player);
	printf("player pos x: %d and player pos y: %d\n", player.pos_x, player.pos_y);

	mlx_key_hook(data.win, key_press, &data);
	//mlx_loop_hook(data.mlx, key_press, &data);

	mlx_hook(data.win, 17, 1L<<17, close_window, &data);
	mlx_loop(data.mlx);
}

