/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:59:34 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/21 12:17:42 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	ft_strlen_solong(const char *str)
{
	int	x;

	x = 0;
	while (str[x] != '\0')
	{
		x++;
	}
	return (x - 1);
}

int	how_many_lines(char *str, t_data *data)
{
	int	fd;
	int	lines;

	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open file");
		exit(1);
	}
	lines = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		lines++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

int	init_data(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	data->map.width = ft_strlen_solong(data->map_two_d[y]);
	data->collectible_count = 0;
	data->exit_accessible = 0;
	data->moves = 0;
	data->exit_unlocked = 0;
	data->collectible_collected = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map_two_d[y][x] == 'P')
			{
				data->player.pos_x = x;
				data->player.pos_y = y;
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	draw_win(t_data *data)
{
	if (data->won == 1)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->victory,
			2 * SIZE, 2 * SIZE);
	}
	return (0);
}

void	printmove(t_data *data)
{
	data->moves++;
	printf("Moves: %d\n", data->moves);
}

void print_map_debug(t_data *data)
{
    printf("Map width: %d, Map height: %d\n", data->map.width, data->map.height);
    for (int i = 0; i < data->map.height; i++)
    {
        printf("%s\n", data->map_two_d[i]);
    }
}
