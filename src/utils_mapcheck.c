/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mapcheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:23:03 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/07 14:13:49 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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

void only_1_E(t_data *data)
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
}

void only_1_P(t_data *data)
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
}

int atleast_1_C(t_data *data)
{
    int y = 0;
    {
        while (y < data->map.height) 
        {
            int x = 0;
            while( x < data->map.width)
            {
                if(data->map_twoD[y][x] == 'C')
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
    int i = 0;
    while (i < data->map.height) 
    {
        free(data->visited[i]);
        i++;
    }
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

int wrong_elements(t_data *data)
{
    int y = 0;
    {
        while (y < data->map.height) 
        {
            int x = 0;
            while( x < data->map.width)
            {
                if(data->map_twoD[y][x] != 'C'&&data->map_twoD[y][x] != 'P'&&data->map_twoD[y][x] != '0'&&data->map_twoD[y][x] != '1'&&data->map_twoD[y][x] != 'E')
                {
                    printf("Wrong elements in Map\n");
                    exit(EXIT_FAILURE);
                }
                x++;
            }
            y++;
        }
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
    wrong_elements(data);
    closed_by_walls(data);
    only_1_E(data);
    only_1_P(data);
    atleast_1_C(data);
    allocate_visited(data);
    access_collectible(data);
    return(0);
}