/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:59:34 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/08 13:57:07 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	line_length(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i - 1);
}

int	how_many_lines(char *str)
{
	int	fd;
	int	lines;

	fd = open(MAP_PATH, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open file");
		return (1);
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

// i moved data->won and data->collectible_accessible
int	init_data(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	data->map.width = line_length(data->map_two_d[y]);
	data->collectible_count = 0;
	data->exit_accessible = 0;
	data->moves = -1;
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
