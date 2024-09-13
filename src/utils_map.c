/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:49 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/08 16:59:22 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	load_texture(t_data *data)
{
	int	p;
	int	t;

	data->won = 0;
	data->floor = mlx_xpm_file_to_image(data->mlx, "texture/sandfloor.xpm", &p,
			&t);
	data->wall = mlx_xpm_file_to_image(data->mlx, "texture/wall.xpm", &p, &t);
	data->collectible = mlx_xpm_file_to_image(data->mlx, "texture/coin.xpm", &p,
			&t);
	data->exit = mlx_xpm_file_to_image(data->mlx, "texture/exit.xpm", &p, &t);
	data->actor = mlx_xpm_file_to_image(data->mlx, "texture/wizard.xpm", &p,
			&t);
	data->victory = mlx_xpm_file_to_image(data->mlx, "texture/victory.xpm", &p,
			&t);
	return (0);
}

//	void	map_two_d(t_data *data)
//	{
//		int	fd;
//		int	i;
//	
//		i = 0;
//		fd = open(data->map_path, O_RDONLY);
//		if (fd < 0)
//		{
//			printf("Failed to open file");
//			exit(EXIT_FAILURE);
//		}
//		data->map.height = how_many_lines(NULL, data);
//		data->map_two_d = malloc(sizeof(char *) * (data->map.height + 1));
//		data->map_two_d[0] = get_next_line(fd);
//		while (i < data->map.height)
//		{
//			i++;
//			data->map_two_d[i] = get_next_line(fd);
//		}
//		data->map_two_d[i] = NULL;
//		if (data->map.height == 0 || data->map_two_d == NULL)
//		{
//			printf("Map empty\n");
//			exit(EXIT_FAILURE);
//		}
//		close(fd);
//	}

void map_two_d(t_data *data)
{
    int fd;
    int i;

    i = 0;
    fd = open(data->map_path, O_RDONLY);
    if (fd < 0)
    {
        printf("Failed to open file");
        exit(EXIT_FAILURE);
    }
    data->map.height = how_many_lines(NULL, data);
    data->map_two_d = malloc(sizeof(char *) * (data->map.height + 1));
    if (!data->map_two_d)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    while (i < data->map.height)
    {
        char *line = get_next_line(fd);
        if (line)
        {
            // Remove newline character if present
            line[strcspn(line, "\n")] = '\0';
            data->map_two_d[i] = line;
        }
        else
        {
            data->map_two_d[i] = NULL;
        }
        i++;
    }
    data->map_two_d[i] = NULL;

    if (data->map.height == 0 || data->map_two_d == NULL)
    {
        printf("Map empty\n");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

