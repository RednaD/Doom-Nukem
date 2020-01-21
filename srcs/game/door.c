/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 19:19:36 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/21 21:17:56 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <math.h>

void			doors(t_env *env, float x, float y)
{
	if (fabs(env->dir_x) > fabs(env->dir_y))
	{
		if (env->map[(int)y][(int)(x + env->dir_x)] == env->dr.h_door &&
				env->pos_z <= 1)
			env->map[(int)y][(int)(x + env->dir_x)] = env->dr.h_door_o;
		else if (env->map[(int)y][(int)(x + env->dir_x)] == env->dr.h_door_o &&
				env->map[(int)y][(int)x] != env->dr.h_door_o && env->pos_z <= 1)
			env->map[(int)y][(int)(x + env->dir_x)] = env->dr.h_door;
	}
	else if (fabs(env->dir_x) < fabs(env->dir_y))
	{
		if (env->map[(int)(y + env->dir_y)][(int)x] == env->dr.v_door &&
				env->pos_z <= 1)
			env->map[(int)(y + env->dir_y)][(int)x] = env->dr.v_door_o;
		else if (env->map[(int)(y + env->dir_y)][(int)x] == env->dr.v_door_o &&
				env->map[(int)y][(int)x] != env->dr.v_door_o && env->pos_z <= 1)
			env->map[(int)(y + env->dir_y)][(int)x] = env->dr.v_door;
	}
	if (((env->map[(int)y][(int)(x + env->dir_x)] == END &&
			fabs(env->dir_x) > fabs(env->dir_y)) ||
			(env->map[(int)(y + env->dir_y)][(int)x] == END &&
			fabs(env->dir_x) < fabs(env->dir_y))) && env->pos_z <= 1)
		env->victory = 1;
}

static void		door_side_entry(t_env *env)
{
	if (
		env->map[env->map_y][env->map_x] < 9 &&
				env->wll.side == 0 && env->wll.rdx < 0 &&
				env->map[env->map_y][env->map_x + 1] == env->dr.v_door_o)
		env->wll.tex_i = env->dr.door2;
	else if (
		env->map[env->map_y][env->map_x] < 9 &&
				env->wll.side == 0 && env->wll.rdx > 0 &&
				env->map[env->map_y][env->map_x - 1] == env->dr.v_door_o &&
				(env->map[env->map_y][env->map_x - 2] <= 0 ||
				env->map[env->map_y][env->map_x - 2] >= 9))
		env->wll.tex_i = env->dr.door2;
	if (
		env->map[env->map_y][env->map_x] < 9 &&
				env->wll.side == 1 && env->wll.rdy < 0 &&
				env->map[env->map_y + 1][env->map_x] == env->dr.h_door_o)
		env->wll.tex_i = env->dr.door2;
	else if (
		env->map[env->map_y][env->map_x] < 9 &&
				env->wll.side == 1 && env->wll.rdy > 0 &&
				env->map[env->map_y - 1][env->map_x] == env->dr.h_door_o &&
				(env->map[env->map_y - 2][env->map_x] <= 0 ||
				env->map[env->map_y - 2][env->map_x] >= 9))
		env->wll.tex_i = env->dr.door2;
}

void			door_side(t_env *env)
{
	if (env->map[env->map_y][env->map_x] == env->dr.v_door &&
			env->wll.side == 0)
		env->wll.tex_i = env->dr.door2;
	if (env->map[env->map_y][env->map_x] == env->dr.h_door &&
			env->wll.side == 1)
		env->wll.tex_i = env->dr.door2;
	door_side_entry(env);
}
