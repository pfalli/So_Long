/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:20:06 by pfalli            #+#    #+#             */
/*   Updated: 2024/04/23 10:20:06 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// TO DO
// what if inside the map there is another number not handled? example 9 2 5 or letters
// what if map is empty?

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    printf("EXIT\n");
    exit(0);
}

int load_texture(t_data *data) // function for texture
{
	int p, t;

	data->floor = mlx_xpm_file_to_image(data->mlx, "texture/floor.xpm", &p, &t);
	data->wall = mlx_xpm_file_to_image(data->mlx, "texture/wall.xpm", &p, &t);
	data->collectible = mlx_xpm_file_to_image(data->mlx, "texture/pinky.xpm", &p, &t);
	data->exit = mlx_xpm_file_to_image(data->mlx, "texture/exit.xpm", &p, &t);
	data->actor = mlx_xpm_file_to_image(data->mlx, "texture/wizard.xpm", &p, &t);
	return(0);
}

int line_length (char *str)
{
    int i = 0;

    while (str[i] && str[i] != '\n')
        i++;
    return(i - 1);
}


int how_many_lines(char *str)
{
    int fd = open(MAP_PATH, O_RDONLY);
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
    return (lines);
}

void map_twoD(t_data *data)
{
	int fd = open(MAP_PATH, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        return ;
    }
    data->map.height = how_many_lines(NULL);
    data->map_twoD = malloc(sizeof(char *) * (data->map.height + 1));
    data->map_twoD[0] = get_next_line(fd);
	int i = 0;
	while (i < data->map.height)
	{
		i++;
		data->map_twoD[i] = get_next_line(fd);
	}
	close(fd);
}

int closed_by_walls(t_data *data) // IMPORTANT  if I use map.height or width for the index NO - 1 / as a x y coordinate YES
{
    int y = 0;
    int x = 0;
    while (x < data->map.width)
    {
        if (data->map_twoD[0][x] != '1' || data->map_twoD[data->map.height - 1][x] != '1')
        {
            printf("Map not closed by walls\n");
            exit(EXIT_FAILURE);
        }
        x++;
    }
    while (y < data->map.height)
    {
        if (data->map_twoD[y][0] != '1' || data->map_twoD[y][data->map.width - 1] != '1')
        {
            printf("Map not closed by walls\n");
            exit(EXIT_FAILURE);
        }
        y++;
    }
    return(0);
}

int only_1_E(t_data *data)
{
    int y = 0;
    int flag = 0;
    {
        while (y < data->map.height) 
        {
            int x = 0;
            while( x < data->map.width)
            {
                if(data->map_twoD[y][x] == 'E')
                    flag++;
                x++;
            }
            y++;
        }
        if ( flag > 1)
        {
            printf("Too many Exits\n");
            exit(EXIT_FAILURE);
        }
        if (flag == 0)
        {
            printf("No Exits\n");
            exit(EXIT_FAILURE);
        }
    }
    return(0);
}

int only_1_P(t_data *data)
{
    int y = 0;
    int flag = 0;
    {
        while (y < data->map.height) 
        {
            int x = 0;
            while( x < data->map.width)
            {
                if(data->map_twoD[y][x] == 'P')
                    flag++;
                x++;
            }
            y++;
        }
        if ( flag > 1)
        {
            printf("Too many Players\n");
            exit(EXIT_FAILURE);
        }
        if (flag == 0)
        {
            printf("No Player\n");
            exit(EXIT_FAILURE);
        }
    }
    return(0);
}

int atleast_1_C(t_data *data)
{
    int y = 0;
    int flag = 0;
    {
        while (y < data->map.height) 
        {
            int x = 0;
            while( x < data->map.width)
            {
                if(data->map_twoD[y][x] == 'C')
                {
                    flag++;
                    data->collectible_count++;
                }
                x++;
            }
            y++;
        }
        if (flag == 0)
        {
            printf("No Collectibles\n");
            exit(EXIT_FAILURE);
        }
    }
    return(0);
}

void is_exit_accessible(t_data *data, int x, int y) // player pos_x and y
{
    if (data->map_twoD[y][x] == '1' || y < 0 || x < 0 || x >= data->map.width || y >= data->map.height)
        return;
    if (data->visited[y][x])
        return;
    data->visited[y][x] = 1;
    if (data->map_twoD[y][x] == 'E')
        data->exit_accessible = 1;
    if (data->map_twoD[y][x] == 'C')
        data->collectible_accessible++;  
    is_exit_accessible(data, x - 1, y);
    is_exit_accessible(data, x + 1, y);
    is_exit_accessible(data, x, y - 1);
    is_exit_accessible(data, x, y + 1);
    return;
}

int allocate_visited(t_data *data)
{
    data->visited = malloc(sizeof(int*) * data->map.height);
    for (int i = 0; i < data->map.height; i++) {
        data->visited[i] = malloc(sizeof(int) * data->map.width);
        for (int j = 0; j < data->map.width; j++) {
            data->visited[i][j] = 0;
        }
    }
    is_exit_accessible(data, data->player.pos_x, data->player.pos_y);
    if (data->exit_accessible == 0)
    {
        printf("Exit is not accessible from the current position.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < data->map.height; i++)
        free(data->visited[i]);
    free(data->visited);
    return(0);
}

int access_collectible(t_data *data)
{
    if (data->collectible_count != data->collectible_accessible)
    {
        printf("All collectible are not accessible.\n");
        exit(EXIT_FAILURE);
    }
    return(0);
}

int check_map_errors(t_data *data)
{
    int y = 0;
    while (y < data->map.height - 1)
    {
        if (line_length(data->map_twoD[y]) != data->map.width)
        {
            printf("Map not rectangular\n");
            exit(EXIT_FAILURE);
        }
        y++;
    }
    closed_by_walls(data);
    only_1_E(data);
    only_1_P(data);
    atleast_1_C(data);
    allocate_visited(data);
    access_collectible(data);
    return(0);
}

//-----------------------------------------------------------------------------

int draw_wall_floor(t_data *data)
{
    int y = 0;
    while (y < data->map.height)
    {
        int x = 0;
        while (x < data->map.width) // to exclude the last char 14 "\r\n"
        {
            if  (data->map_twoD[y][x] == '1')
                mlx_put_image_to_window(data->mlx, data->win, data->wall, x*SIZE, y*SIZE);
            else if (data->map_twoD[y][x] == '0' ||data->map_twoD[y][x] == 'P' || data->map_twoD[y][x] == 'C' || data->map_twoD[y][x] == 'E' )
                mlx_put_image_to_window(data->mlx, data->win, data->floor, x*SIZE, y*SIZE);
            x++;
        }
        y++;
    }
    return(0);
}

int draw_others(t_data *data)
{
    int y = 0;
    while (y < data->map.height)
    {
        int x = 0;
        while (x < data->map.width) // to exclude the last char 14 "\r\n"
        {
            if  (data->map_twoD[y][x] == 'C')
                mlx_put_image_to_window(data->mlx, data->win, data->collectible, x*SIZE, y*SIZE);
            else if (data->map_twoD[y][x] == 'E')
                mlx_put_image_to_window(data->mlx, data->win, data->exit, x*SIZE, y*SIZE);
            x++;
        }
        y++;
    }
    return(0);
}

int init_data(t_data *data)
{
    int y = 0;
    data->map.width = line_length(data->map_twoD[y]);
    data->won = 0;
    data->collectible_count = 0;
    data->exit_accessible = 0;
    data->collectible_accessible = 0;
    while (y < data->map.height)
    {
        int x = 0;
        while (x < data->map.width) // to exclude the last char 14 "\r\n"
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

int draw_player(t_data *data)
{
    mlx_put_image_to_window(data->mlx, data->win, data->actor, data->player.pos_x*SIZE, data->player.pos_y*SIZE);
    return(0);
}

int draw_all_map(t_data *data)
{
    draw_wall_floor(data);
    draw_others(data);
    draw_player(data);
    return(0);
}

//-----------------------------------------------------------------------------------------

int move_player(t_data *data) // IMPORTANT : first Y then x
{
    if(data->map_twoD[data->player.pos_y][data->player.pos_x] == 'C')
        data->map_twoD[data->player.pos_y][data->player.pos_x] = '0';
    else if (data->map_twoD[data->player.pos_y][data->player.pos_x] == 'E')
    {
        data->map_twoD[data->player.pos_y][data->player.pos_x] = '0';
        data->won = 1;
    }
    draw_all_map(data);
    return(0);
}

int key_press(int keycode, t_data *data)
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
    move_player(data);
	return(0);
}



int main(void)
{
	t_data data;

	data.mlx = mlx_init();
	
	//data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	load_texture(&data);
    map_twoD(&data);
   
    init_data(&data);
    check_map_errors(&data);
    data.win = mlx_new_window(data.mlx, data.map.width*SIZE - 1, data.map.height*SIZE, "Sotomayor");
    draw_all_map(&data);
    mlx_key_hook(data.win, key_press, &data);


	mlx_hook(data.win, 17, 1L<<17, close_window, &data);
    //mlx_loop_hook(data.mlx, draw_all_map, &data);
	mlx_loop(data.mlx);
}


