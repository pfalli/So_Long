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

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define TS 64
# define SIZE 40
# define MAP_PATH "map/nopath.ber"

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
    char        *addr;
    t_player    player;
    t_map       map; // it works only with integers. didn't work with textures
    char        **map_twoD;
    void        *actor;
    void        *exit;
    void        *collectible;
    void        *wall;
    void        *floor;
    int         won;
    char        **visited;
    int         exit_accessible;
    int         collectible_accessible;
    int         collectible_count;
}				t_data;



#endif