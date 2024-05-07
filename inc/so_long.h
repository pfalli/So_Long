/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:40:32 by pfalli            #+#    #+#             */
/*   Updated: 2024/05/07 15:44:40 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "../libft_full/inc/get_next_line.h"
#include "../libft_full/inc/ft_printf.h"
#include "../libft_full/inc/get_next_line.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define TS 40
# define SIZE 40
# define MAP_PATH "map/valid.ber"

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
    void        *victory;
    int         won;
    char        **visited;
    int         exit_accessible;
    int         collectible_accessible;
    int         collectible_count;
    int         collectible_collected;
    int         moves;
    int         exit_unlocked;
}				t_data;

// Map
int load_texture(t_data *data);
void map_twoD(t_data *data);

// Draw map
int draw_wall_floor(t_data *data);
int draw_others(t_data *data);
int init_data(t_data *data);
int draw_player(t_data *data);
int draw_all_map(t_data *data);
int move_player(t_data *data);

// Control
int key_press(int keycode, t_data *data);

// Free
void free_map(t_data *data);
void free_mlx(t_data *data);
void free_images(t_data *data);

// Map check
int closed_by_walls(t_data *data);
void only_1_E(t_data *data);
void only_1_P(t_data *data);
int atleast_1_C(t_data *data);
void is_exit_accessible(t_data *data, int x, int y);
int allocate_visited(t_data *data);
int access_collectible(t_data *data);
int wrong_elements(t_data *data);
int check_map_errors(t_data *data);


int close_window(t_data *data);
int how_many_lines(char *str);
int line_length (char *str);

int draw_win(t_data *data);

#endif