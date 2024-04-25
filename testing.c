/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:03:25 by pfalli            #+#    #+#             */
/*   Updated: 2024/04/23 10:03:25 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    printf("EXIT\n");
    exit(0);
}

int load_texture(t_texture *texture, t_data *data) // function for texture
{
	int p, t;

	texture->floor = mlx_xpm_file_to_image(data->mlx, "texture/floor.xpm", &p, &t);
	texture->wall = mlx_xpm_file_to_image(data->mlx, "texture/wall.xpm", &p, &t);
	texture->collectible = mlx_xpm_file_to_image(data->mlx, "texture/pinky.xpm", &p, &t);
	texture->exit = mlx_xpm_file_to_image(data->mlx, "texture/exit.xpm", &p, &t);
	texture->player = mlx_xpm_file_to_image(data->mlx, "texture/wizard.xpm", &p, &t);
	return(0);
}

int line_length (char *str)
{
    int i = 0;

    while (str[i] && str[i] != '\n')
        i++;
    return(i);
}


int how_many_lines(char *str)
{
    int fd = open("map/valid.ber", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }
    int lines = 0;
    while ((str = get_next_line(fd)) != NULL) {
        lines++;
        free(str);
    }
    close(fd);
    return lines;
}

void map_twoD(t_data *data)
{
	int fd = open("map/valid.ber", O_RDONLY);
    //  if (fd < 0) {
    //      perror("Failed to open file");
    //      return ;
    //  }
    data->map.lines = how_many_lines(NULL);
    data->map_twoD = malloc(sizeof(char *) * (data->map.lines + 1));
    data->map_twoD[0] = get_next_line(fd);
	int i = 0;
	while (i < data->map.lines - 1)
	{
		i++;
		data->map_twoD[i] = get_next_line(fd);
	}
	close(fd);
}

int draw_wall_floor(t_texture *texture, t_data *data)
{
    int y = 0;
    int  end = line_length(data->map_twoD[y]);
    while (y < data->map.lines)
    {
        int x = 0;
        while (x < end - 1) // to exclude the last char 14 "\r\n"
        {
            if  (data->map_twoD[y][x] == '1')
                mlx_put_image_to_window(data->mlx, data->win, texture->wall, x*SIZE, y*SIZE);
            else
                mlx_put_image_to_window(data->mlx, data->win, texture->floor, x*SIZE, y*SIZE);
            x++;
        }
        y++;
    }
    return(0);
}

int draw_others(t_texture *texture, t_data *data)
{
    int y = 0;
    int  end = line_length(data->map_twoD[y]);
    while (y < data->map.lines)
    {
        int x = 0;
        while (x < end - 1) // to exclude the last char 14 "\r\n"
        {
            if  (data->map_twoD[y][x] == 'C')
                mlx_put_image_to_window(data->mlx, data->win, texture->collectible, x*SIZE, y*SIZE);
            else if (data->map_twoD[y][x] == 'E')
                mlx_put_image_to_window(data->mlx, data->win, texture->exit, x*SIZE, y*SIZE);
            x++;
        }
        y++;
    }
    return(0);
}

int player_pos(t_data *data)
{
    int y = 0;
    int  end = line_length(data->map_twoD[y]);
    while (y < data->map.lines)
    {
        int x = 0;
        while (x < end - 1) // to exclude the last char 14 "\r\n"
        {
            if (data->map_twoD[y][x] == 'P')
            {
                data->player.pos_x = x;
                data->player.pos_y = y;
            }
            x++;
        }
        y++;
    }
    return(0);
}

int draw_player(t_texture *texture, t_data *data)
{
    mlx_put_image_to_window(data->mlx, data->win, texture->player, data->player.pos_x*SIZE, data->player.pos_y*SIZE);
    return(0);
}

int draw_all_map(t_texture *texture, t_data *data)
{
    draw_wall_floor(texture, data);
    draw_others(texture, data);
    draw_player(texture, data);
    return(0);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == ESC)
		close_window(data);
	if (keycode == A)
		data->player.pos_x -= 1;
	else if ( keycode == W)
		data->player.pos_y -= 1;
	else if (keycode == D)
		data->player.pos_x += 1;
	else if (keycode == S )
		data->player.pos_y += 1;
	return(0);
}

//  int move_player(t_data *data)
//  {
//      if('C')
//  
//      if('E')
//  
//      if('1')
//  
//      if('0')
//      
//  }


int main(void)
{
	t_data data;
    t_texture texture;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_SIZE_X, WIN_SIZE_Y, "Sotomayor");
	//data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	load_texture(&texture, &data);
    map_twoD(&data);

    player_pos(&data);
    draw_player(&texture, &data);
    mlx_key_hook(data.win, key_press, &data);


	mlx_hook(data.win, 17, 1L<<17, close_window, &data);
    mlx_loop_hook(data.mlx, key_press, &data);
	mlx_loop(data.mlx);
}
