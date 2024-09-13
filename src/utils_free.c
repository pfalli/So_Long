/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:10:18 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/08 16:09:54 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.height)
	{
		free(data->map_two_d[i]);
		i++;
	}
	free(data->map_two_d);
}

void	free_mlx(t_data *data)
{
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	free_images(t_data *data)
{
	mlx_destroy_image(data->mlx, data->floor);
	mlx_destroy_image(data->mlx, data->wall);
	mlx_destroy_image(data->mlx, data->actor);
	mlx_destroy_image(data->mlx, data->collectible);
	mlx_destroy_image(data->mlx, data->exit);
	mlx_destroy_image(data->mlx, data->victory);
}

void	free_visited(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.height)
	{
		free(data->visited[i++]);
	}
	free(data->visited);
}
