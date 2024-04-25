/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:40:32 by pfalli            #+#    #+#             */
/*   Updated: 2024/04/17 11:40:32 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <mlx.h>
#include "libft_full/inc/get_next_line.h"

# define MAP_SIZE 100
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define TS 64
# define WIN_SIZE_X 1000
# define WIN_SIZE_Y 400
# define SIZE 40

typedef struct s_player {
    int         pos_x;
    int         pos_y;
    int         position_start;
    int         count_moves;
    bool        is_initialized;
}               t_player;


typedef struct s_texture {
    void        *player;
    void        *exit;
    void        *collectible;
    void        *wall;
    void        *floor;
}               t_texture;

typedef struct s_map {
    void        *map_path;
    int         width;
    int         height;
    int         point_x;
    int         point_y;
    int         lines;
}               t_map;

typedef struct	s_data {
	void 		*mlx;
	void 		*win;
    void        *img;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    char        *addr;
    t_player    player;
    t_texture   texture;
    t_map       map;
    char        **map_twoD;
    bool        won;
    int         point_x;
    int         point_y;
}				t_data;



#endif