/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:57:25 by pfalli            #+#    #+#             */
/*   Updated: 2024/04/18 11:57:25 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int update_player_position(t_data *data, t_player *player)
{
	
}

int key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 97) // A
		update_player_position;
	else if ( keycode == 119) // W
		update_player_position;
	else if (keycode == 100) // D
		update_player_position;
	else if (keycode == 115 )// S
		update_player_position;
}