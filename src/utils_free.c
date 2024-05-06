/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:10:18 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/03 11:10:18 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_map(t_data *data)
{
    int i = 0;
    while (i < data->map.height)
    {
        free(data->map_twoD[i]);
        i++;
    }
    free(data->map_twoD);           // map
}

void free_mlx(t_data *data)
{
    mlx_destroy_display(data->mlx); // display
    free(data->mlx);                // mlx pointer
}

void free_images(t_data *data)
{
    mlx_destroy_image(data->mlx, data->floor);
    mlx_destroy_image(data->mlx, data->wall);
    mlx_destroy_image(data->mlx, data->actor);
    mlx_destroy_image(data->mlx, data->collectible);
    mlx_destroy_image(data->mlx, data->exit);
    mlx_destroy_image(data->mlx, data->victory);
}