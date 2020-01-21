/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:38:02 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/22 14:37:18 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <math.h>

/*
** @desc			renders the sky texture
** @param env		main game structure
** @param x			horizontal screen pixel coordinate
** @param ds		max value for the rendering loop
*/

static void			draw_sky(t_env *env, int x, int ds)
{
	float	sky;
	int		y;
	t_text	text;

	text = env->text_wll[7];
	if (env->dir_x * -1.f < -1.f)
		sky = asin(-1.f);
	else
		sky = asin(env->dir_x * -1.f);
	if (env->dir_y < 0)
		sky *= -1.f;
	sky += M_PI;
	sky += x * 60 * 2 * M_PI / 360 / W_WIDTH - 30 * 2 * M_PI / 360;
	sky += (sky < 0) ? 2 * M_PI : 0;
	sky -= (sky > 2 * M_PI) ? 2 * M_PI : 0;
	env->skyx = sky * text.w / (2 * M_PI);
	y = 0;
	while (y <= ds)
	{
		env->skyy = (W_HEIGHT / 2 + y - env->rot) * text.h / W_HEIGHT;
		get_rgb_color(env, text.str[env->skyy * text.w + env->skyx]);
		pixel_put(env, x, y, env->color);
		y++;
	}
}

/*
** @desc			gets the texture index from text_wll struct
** @param map		value parsed from the map file
*/

static int			get_wall_texture(t_env *env, int map)
{
	if (map >= 0 && map <= 6)
		return (map - 1);
	if (map == 9)
		return (6);
	if (map == 7 || map == 8)
		return (env->dr.door1);
	return (0);
}

/*
** @desc			2nd part of wall drawing
** @param env		main game structure
** @param x			horizontal screen pixel coordinate
** @param map		value parsed from the map file
*/

static void			draw_wall2(t_env *env, int x)
{
	t_text	text;

	while (env->wll.drawstart++ < env->wll.drawend - 1)
	{
		env->wll.tex_y = (env->wll.drawstart - W_HEIGHT / 2 +
			(env->wll.lineheight / 2) * (-env->pos_z + 1) - env->rot) *
			64 / env->wll.lineheight;
		door_side(env);
		if (env->wll.decal)
			decal(env);
		text = env->text_wll[env->wll.tex_i];
		get_wall_fog(env, *(int*)(&text.str[env->wll.tex_y *
			text.w + env->wll.tex_x]));
		pixel_put(env, x, env->wll.drawstart, env->color);
	}
}

/*
** @desc			renders the wall textures
** @param env		main game structure
** @param x			horizontal screen pixel coordinate
** @param map		value parsed from the map file
*/

void				draw_wall(t_env *env, int x, int map)
{
	if (env->wll.side == 0)
		env->wll.wall_x = env->pos_y + env->wll.pwd * env->wll.rdy;
	else
		env->wll.wall_x = env->pos_x + env->wll.pwd * env->wll.rdx;
	env->wll.wall_x -= floor(env->wll.wall_x);
	env->wll.tex_x = abs(64 - (int)(env->wll.wall_x * 64) - 1) % 64;
	env->wll.tex_i = get_wall_texture(env, map);
	if (env->sky_mode == 2)
		draw_floor_or_ceiling(env, x, 1, env->text_wll[4]);
	else
		draw_sky(env, x, env->wll.drawstart);
	draw_floor_or_ceiling(env, x, 0, env->text_wll[5]);
	draw_wall2(env, x);
}
