/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:49 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/07 13:07:22 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int load_texture(t_data *data) // function for texture
{
	int p, t;

	data->floor = mlx_xpm_file_to_image(data->mlx, "texture/sandfloor.xpm", &p, &t);
	data->wall = mlx_xpm_file_to_image(data->mlx, "texture/wall.xpm", &p, &t);
	data->collectible = mlx_xpm_file_to_image(data->mlx, "texture/coin.xpm", &p, &t);
	data->exit = mlx_xpm_file_to_image(data->mlx, "texture/exit.xpm", &p, &t);
	data->actor = mlx_xpm_file_to_image(data->mlx, "texture/wizard.xpm", &p, &t);
    data->victory = mlx_xpm_file_to_image(data->mlx, "texture/victory.xpm", &p, &t);
	return(0);
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
    if (data->map.height == 0 || data->map_twoD == NULL)
    {
        printf("Map empty\n");
        exit(EXIT_FAILURE);
    }
	close(fd);
}