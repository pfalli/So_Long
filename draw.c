/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:44:49 by pfalli            #+#    #+#             */
/*   Updated: 2024/04/19 13:44:49 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int load_textures(t_texture *texture, t_data *data) // function for textures
{
	int x, j;

	texture->floor = mlx_xpm_file_to_image(data->mlx, "textures/floor.xpm", &x, &j);
	texture->wall = mlx_xpm_file_to_image(data->mlx, "textures/wall.xpm", &x, &j);
	texture->collectible = mlx_xpm_file_to_image(data->mlx, "textures/coin.xpm", &x, &j);
	texture->exit = mlx_xpm_file_to_image(data->mlx, "textures/exit.xpm", &x, &j);
	texture->player = mlx_xpm_file_to_image(data->mlx, "textures/person.xpm", &x, &j);
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
			x += TILE_SIZE;
		}
		else if ( c == '\n')
		{
			y += TILE_SIZE;
			x = 0;
		}
		else if (c != '\r')
		{
			mlx_put_image_to_window(data->mlx, data->win, texture->floor, x, y);
			x += TILE_SIZE;
		}
	}
	close (fd);
	mlx_destroy_image(data->mlx, texture->wall);
	mlx_destroy_image(data->mlx, texture->floor);
	return(0);
}


int draw_all_map(t_texture *texture, t_data *data)
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
			y += TILE_SIZE;
			x = 0;
		}
		else if (c == 'E')
		{
        	mlx_put_image_to_window(data->mlx, data->win, texture->exit, x, y);
			x += TILE_SIZE;
		}
		else if (c == 'P')
		{
			mlx_put_image_to_window(data->mlx, data->win, texture->player, x, y);
			x += TILE_SIZE;
		}
		else if ( c != '\r' ||  c != '0' ||  c != '1')
			x += TILE_SIZE;
	}
	if (status == -1)
    {
        perror("Error reading file");
        return (1);
    }
	close (fd);
	return(0);
	
}
