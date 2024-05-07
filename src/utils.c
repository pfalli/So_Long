/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:59:34 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/07 15:45:09 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"


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

int init_data(t_data *data)
{
    int y = 0;
    data->map.width = line_length(data->map_twoD[y]);
    data->won = 0;
    data->collectible_count = 0;
    data->exit_accessible = 0;
    data->collectible_accessible = 0;
    data->moves = -1;
    data->exit_unlocked = 0;
    data->collectible_collected = 0;
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

int draw_win(t_data *data)
{
    if(data->won == 1)
    {
        mlx_put_image_to_window(data->mlx, data->win, data->victory, 3*SIZE, 3*SIZE);
    }
    return(0);
}