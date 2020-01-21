/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doomnukem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 13:36:39 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/22 15:49:20 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_H
# define DOOMNUKEM_H
# include "../../libs/libft/libft.h"
# include "../../libs/minilibx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>

# define BOX_COUNT 32
# define BOX_WIDTH 32 + 1
# define BOX_HEIGHT 32 + 1
# define GRID_WIDTH BOX_COUNT * (BOX_WIDTH)
# define GRID_HEIGHT BOX_COUNT * (BOX_HEIGHT)
# define WINDOW_WIDTH 1800
# define WINDOW_HEIGHT (GRID_HEIGHT)
# define WINDOW_TITLE "Doom Nukem - Editor"
# define FILE_EXTENSION ".dn"

# define LIFE_LEVEL_WIDTH 20
# define LIFE_LEVEL_HEIGHT 100

# define KEYPRESS 2
# define KEYPRESSMASK (1L<<0)
# define KEYCODE_ESC 53
# define KEYCODE_RIGHT_ARROW 124
# define KEYCODE_LEFT_ARROW 123
# define KEYCODE_UP_ARROW 126
# define KEYCODE_DOWN_ARROW 125
# define MOUSE_RIGHT_CLICK 2
# define MOUSE_LEFT_CLICK 1
# define KEYCODE_S 1
# define KEYCODE_P 35
# define KEYCODE_M 46
# define KEYCODE_E 14

# define WALL_MODE 0
# define SPAWN_MODE 1
# define SPRITE_MODE 2
# define END_MODE 3

# define SKY_MODE_OPEN 1
# define SKY_MODE_CLOSED 2

# define SPAWN_ID 100
# define END_ID 63

# define CHECKBOX1_X 1220
# define CHECKBOX1_Y 925
# define CHECKBOX2_X 1470
# define CHECKBOX2_Y 925
# define CHECKBOX_WH 50

# define HT1 "Press left/right arrow to change texture"
# define HT2 "Press 'm' to change texture mode (wall/sprite)"
# define HT3 "Press 's' to save + exit and 'esc' to quit"
# define HT4 "Press the left mouse button to put a wall / player position"
# define HT5 "Press the right mouse button to take off wall / player position"
# define HT6 "Press 'P' to activate/desactivate the spawn mode"
# define HT7 "Press 'E' to activate/desactivate the end mode"
# define TEXT_CURRENT_TEXTURE "Current texture:"
# define TEXT_LIFE_LEVEL "Life level:"
# define TEXT_LIFE_LEVEL_2 "(Use up/down)"
# define TEXT_SKYMODE_OPEN "Open sky"
# define TEXT_SKYMODE_CLOSE "Closed sky"

# include "structs.h"
# include "../game/xpm_parser_struct.h"
# include "prototypes.h"

/*
** loader_xpm.c
*/
t_text				load_xpm(t_env *env, const char *name);

/*
** loader_utils.c
*/

t_color_p			get_color(t_env *env, char *line, t_parser *p);
unsigned int		rvb_to_ui(t_env *env, char *src);
int					ft_atoi_base2(char *src, int base);

#endif
