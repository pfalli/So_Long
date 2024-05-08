/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:20:06 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/08 11:03:41 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

// TO DO:
// after exit count moves
// count moves of any keyboard clicked
// count moves after the wall DONE

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	load_texture(&data);
	map_two_d(&data);
	init_data(&data);
	check_map_errors(&data);
	data.win = mlx_new_window(data.mlx, data.map.width * SIZE - 1,
			data.map.height * SIZE, "Sotomayor");
	draw_all_map(&data);
	mlx_key_hook(data.win, key_press, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
