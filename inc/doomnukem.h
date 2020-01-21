/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doomnukem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:31:47 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/22 15:48:49 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_H
# define DOOMNUKEM_H

# define W_WIDTH 1024
# define W_HEIGHT 720
# define KEYPRESS	2
# define KEYRELEASE 3
# define CLOSE		17
# define END		999

# define T1 "      WELCOME BACK, AGENT SERGUEI      "
# define T2 " ONE OF OUR ANCIENT SOLDIER LOST A KEY "
# define T3 "WHO ALLOWED TO OPEN A CHEST CONTAINING "
# define T4 "     THE PLAN OF A LEGENDARY WEAPON    "
# define T5 " YOU KNOW THIS MAZE BETTER THAN ANYONE "
# define T6 "          YOU MUST FIND THIS KEY       "
# define T7 " KILL ALL THOSE WHO WILL BE ON YOU WAY "
# define T8 "            GOD BLESS YOU              "

# if __APPLE__
#  define ESCAPE_KEY		53
#  define CTRL_KEY			256
#  define SHIFT_KEY			257
#  define SPACE_KEY			49
#  define KP_MINUS_KEY		78
#  define KP_PLUS_KEY		69
#  define KP_5_KEY			87
#  define UP_ARROW			126
#  define LEFT_ARROW		123
#  define RIGHT_ARROW		124
#  define DOWN_ARROW		125
#  define A_KEY				0
#  define S_KEY				1
#  define D_KEY				2
#  define W_KEY				13
#  define M_KEY				46
#  define E_KEY				14
#  define G_KEY				5
#  define R_KEY				15

# elif __linux__
#  define ESCAPE_KEY		0xff1b
#  define KP_MINUS_KEY		0xffad
#  define KP_PLUS_KEY		0xffab
#  define KP_5_KEY			0xffb5
#  define UP_ARROW			0xff52
#  define LEFT_ARROW		0xff51
#  define RIGHT_ARROW		0xff53
#  define DOWN_ARROW		0xff54
#  define A_KEY				0x0061
#  define S_KEY				0x0073
#  define D_KEY				0x0064
#  define W_KEY				0x0077
#  define M_KEY				0x006d
# endif

# include "../libs/libft/libft.h"
# include "../libs/minilibx/mlx.h"
# include <time.h>
# include <stdlib.h>
# include "./game/xpm_parser_struct.h"

typedef struct		s_door
{
	int				h_door;
	int				v_door;
	int				h_door_o;
	int				v_door_o;
	int				door1;
	int				door2;
}					t_door;

typedef struct		s_gameloop
{
	clock_t			prevclock;
	clock_t			currclock;
	clock_t			frameclock;
}					t_gameloop;

typedef struct		s_key
{
	int				rot_up;
	int				rot_down;
	int				rot_right;
	int				rot_left;
	int				left;
	int				right;
	int				forward;
	int				backward;
	int				up;
	int				down;
}					t_key;

typedef struct		s_wall_cast
{
	float			sdx;
	float			sdy;
	float			ddx;
	float			ddy;
	int				step_x;
	int				step_y;
	float			plane_x;
	float			plane_y;
	int				tex_x;
	int				tex_y;
	float			wall_x;
	float			rdx;
	float			rdy;
	int				side;
	float			pwd;
	int				drawstart;
	int				drawend;
	int				lineheight;
	float			fog;
	int				tex_i;
	int				decal;
}					t_wall_cast;

typedef struct		s_floor_cast
{
	float			x;
	float			y;
	float			weight;
	float			curr_x;
	float			curr_y;
	int				tex_x;
	int				tex_y;
	float			dist_wall;
	float			dist_player;
	float			current_dist;
}					t_floor_cast;

typedef struct		s_sprite
{
	float			x;
	float			y;
	int				text;
	int				type;
	int				hp;
	int				multi;
	int				anim;
	int				death_anim;
	int				picked;
}					t_sprite;

typedef struct		s_sprite_cast
{
	float			zbuffer[W_WIDTH];
	int				order[1024];
	float			dist[1024];
	t_sprite		data[1024];
	int				nb_sprite;
	float			x;
	float			y;
	float			inv_det;
	float			trans_x;
	float			trans_y;
	int				scr_x;
	int				h;
	int				w;
	int				dsx;
	int				dsy;
	int				dex;
	int				dey;
	int				tex_x;
	int				tex_y;
	int				stripe;
	float			dx;
	float			dy;
	float			angle;
}					t_sprite_cast;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_env
{
	t_gameloop		gl;
	t_text			text_wll[11];
	t_text			text_gui[22];
	t_text			text_spr[22];
	t_wall_cast		wll;
	t_floor_cast	flr;
	t_sprite_cast	spr;
	t_key			key;
	t_color			color;
	int				map[34][34];
	t_door			dr;
	struct s_env	*core;
	int				sky_mode;
	char			*file;
	int				spawn_placed;
	int				fd;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_str;
	int				bpp;
	int				size_line;
	int				endian;
	float			dir_x;
	float			dir_y;
	float			pos_x;
	float			pos_y;
	float			pos_z;
	float			ws;
	float			rs;
	float			cam_x;
	int				map_x;
	int				map_y;
	int				pistol;
	int				firing;
	int				ammo;
	int				mute;
	float			rot;
	int				nt;
	int				jump;
	int				sneak;
	int				fly;
	int				skyx;
	int				skyy;
	float			hp;
	int				btn[2];
	int				state;
	int				gui;
	int				torch;
	int				item_key;
	int				victory;
	int				count_s;
	int				n_gui_str;
}					t_env;

/*
** struct.c
*/
void				init_struct_core(t_env *env);

/*
** parser.c
*/
void				ft_import(t_env *env, char *path, int y);
void				ft_check_file(t_env *env, char *path);

/*
** load_texture.c
*/
void				check_texture_str(t_env *env);

/*
** get_texture.c
*/
void				get_texture_wall(t_env *env);
void				get_texture_gui(t_env *env);
void				get_texture_sprite(t_env *env);

/*
** render.c
*/
void				get_clock_time(t_env *env);
int					redraw(t_env *env);
void				pixel_put(t_env *env, int x, int y, t_color color);
void				render(t_env *env);

/*
** raycast.c
*/
void				*thread_core(void *arg);

/*
** draw_wall.c
*/
void				draw_wall(t_env *env, int x, int text);

/*
** draw_floor_ceiling.c
*/
void				draw_floor_or_ceiling(t_env *env, int x, int side,
	t_text text);

/*
** draw_gui.c
*/
void				draw_image(t_env *env, t_text text, int xp, int yp);
void				draw_weapon(t_env *env, t_text text, int pos_x, int pos_y);
void				draw_gui(t_env *env);

/*
** draw_sprite.c
*/
void				draw_sprite(t_env *env);
void				sort_sprite(t_env *env, int i);
void				*thread_sprite(void *arg);

/*
** draw.sprite2.c
*/
int					get_texture(t_env *env);
void				pixel_put_sprites(t_env *env, int color, int y, int s);

/*
** init_sprite.c
*/
void				create_sprites(t_sprite *spr, float x, float y, int value);
void				init_sprites(t_env *env, int x, int y, int *i);

/*
** data.c
*/
void				exit_doom(t_env *env, char *str, int e);

/*
** hook.c
*/
int					mouse_button_press(int button, int x, int y, t_env *env);
int					mouse_button_release(int button, int x, int y, t_env *env);
int					mouse_motion(int x, int y, t_env *env);
int					key_release(int hook, t_env *env);
int					key_press(int hook, t_env *env);

/*
** utils.c
*/
void				comb_sort(int *order, float *dist, int amount);

/*
** move_xy_axis.c
*/
void				move_handler(t_env *env);

/*
** move_z_axis.c
*/
void				pitch(t_env *env);
void				vertical(t_env *env);

/*
** color.c
*/
void				get_rgb_color(t_env *env, int color);
void				get_wall_fog(t_env *env, int color);
void				get_floor_or_ceiling_fog(t_env *env, int color, int y);
void				get_sprite_fog(t_env *env, int color, float dist);
void				get_rgb_color(t_env *env, int color);

/*
** enemy.c
*/
void				enemy_core(t_env *env, t_sprite *enemy, int s, int i);

/*
** object.c
*/
void				object_core(t_env *env, t_sprite *enemy, int i);

/*
** gui.c
*/
void				main_gui(t_env *env);
void				draw_main_menu_str(t_env *env);

/*
** hud.c
*/
void				main_hud(t_env *env);

/*
** door.c
*/
void				doors(t_env *env, float x, float y);
void				door_side(t_env *env);

/*
** decal.c
*/
void				decal(t_env *env);

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
