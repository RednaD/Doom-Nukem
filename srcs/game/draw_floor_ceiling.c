/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 03:34:03 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/22 14:00:06 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			computes the wall and floor coordinates
** @param env		main game structure
*/

static void			calc_side(t_env *env)
{
	if (env->wll.side == 0 && env->wll.rdx > 0)
	{
		env->flr.x = env->map_x;
		env->flr.y = env->map_y + env->wll.wall_x;
	}
	else if (env->wll.side == 0 && env->wll.rdx < 0)
	{
		env->flr.x = env->map_x + 1.0;
		env->flr.y = env->map_y + env->wll.wall_x;
	}
	else if (env->wll.side == 1 && env->wll.rdy > 0)
	{
		env->flr.x = env->map_x + env->wll.wall_x;
		env->flr.y = env->map_y;
	}
	else
	{
		env->flr.x = env->map_x + env->wll.wall_x;
		env->flr.y = env->map_y + 1.0;
	}
	if (env->wll.drawend < 0)
		env->wll.drawend = W_HEIGHT;
}

/*
** @desc			renders the floor and ceiling textures
** @param env		main game structure
** @param x			horizontal screen pixel coordinate
** @param side		0 if floor ; 1 if ceiling
** @param text		texture used to render floor or ceiling
*/

void				draw_floor_or_ceiling(t_env *env, int x, int side,
	t_text text)
{
	int		y;
	int		drawstart;
	int		size;

	y = (side == 0) ? env->wll.drawend : -1;
	drawstart = (side == 0) ? W_HEIGHT : env->wll.drawstart + 1;
	calc_side(env);
	while (++y < drawstart)
	{
		size = (side == 0) ? y - env->rot - env->pos_z * 64 :
				y - W_HEIGHT - env->rot - env->pos_z * 64;
		env->flr.current_dist = W_HEIGHT / (2.0 * y - W_HEIGHT - 2 * env->rot);
		env->flr.weight = (side == 0) ? env->flr.current_dist / env->wll.pwd *
			(env->pos_z + 1) : (env->flr.current_dist / env->wll.pwd *
			(-env->pos_z + 1)) * -1;
		env->flr.curr_x = env->flr.weight * env->flr.x +
			(1.0 - env->flr.weight) * env->pos_x;
		env->flr.curr_y = env->flr.weight * env->flr.y +
			(1.0 - env->flr.weight) * env->pos_y;
		env->flr.tex_x = (int)(env->flr.curr_x * 64) % 64;
		env->flr.tex_y = (int)(env->flr.curr_y * 64) % 64;
		get_floor_or_ceiling_fog(env, text.str[env->flr.tex_y *
			text.w + env->flr.tex_x], size);
		pixel_put(env, x, y, env->color);
	}
}
