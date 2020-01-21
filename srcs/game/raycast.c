/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:27:43 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/22 14:34:36 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <math.h>

/*
** @desc			computes ray direction
** @param env		main game structure
*/

static void				calc_dir(t_env *env)
{
	if (env->wll.rdx < 0)
	{
		env->wll.step_x = -1;
		env->wll.sdx = (env->pos_x - env->map_x) * env->wll.ddx;
	}
	else
	{
		env->wll.step_x = 1;
		env->wll.sdx = (env->map_x + 1.0 - env->pos_x) * env->wll.ddx;
	}
	if (env->wll.rdy < 0)
	{
		env->wll.step_y = -1;
		env->wll.sdy = (env->pos_y - env->map_y) * env->wll.ddy;
	}
	else
	{
		env->wll.step_y = 1;
		env->wll.sdy = (env->map_y + 1.0 - env->pos_y) * env->wll.ddy;
	}
}

/*
** @desc			computes ray direction
** @param map		value parsed from the map file
** @param x			horizontal pixel screen coordinate
** @return			success if block is a window & x an odd number
*/

static int				window(int map, int x)
{
	if (x % 2 != 0)
	{
		if (map == 9)
			return (1);
	}
	return (0);
}

/*
** @desc			computes Digital Differential Analyzer algorithm
** @param env		main game structure
** @param x			horizontal pixel screen coordinate
** @param map		value parsed from the map file
*/

static void				perform_dda(t_env *env, int x, int map)
{
	while (map <= 0 || window(map, x) || map >= 10)
	{
		if (env->wll.sdx < env->wll.sdy)
		{
			env->wll.sdx += env->wll.ddx;
			env->map_x += env->wll.step_x;
			env->wll.side = 0;
		}
		else
		{
			env->wll.sdy += env->wll.ddy;
			env->map_y += env->wll.step_y;
			env->wll.side = 1;
		}
		map = env->map[env->map_y][env->map_x];
	}
}

/*
** @desc			performs raycast
** @param env		main game structure
** @param x			horizontal pixel screen coordinate
*/

static void				ray_cast(t_env *env, int x)
{
	if (env->wll.side == 0)
		env->wll.pwd = (env->map_x - env->pos_x +
			(1 - env->wll.step_x) / 2) / env->wll.rdx;
	else
		env->wll.pwd = (env->map_y - env->pos_y +
			(1 - env->wll.step_y) / 2) / env->wll.rdy;
	env->wll.fog = (env->wll.pwd < 0.8) ? 1 : 0.8 / env->wll.pwd;
	env->core->spr.zbuffer[x] = env->wll.pwd;
	env->wll.lineheight = (int)(W_HEIGHT / env->wll.pwd);
	env->wll.drawstart = (-env->wll.lineheight / 2);
	env->wll.drawstart -= env->wll.drawstart * env->pos_z;
	env->wll.drawstart += (W_HEIGHT / 2 + env->rot);
	if (env->wll.drawstart < 0)
		env->wll.drawstart = 0;
	env->wll.drawend = (env->wll.lineheight / 2);
	env->wll.drawend += env->wll.drawend * env->pos_z;
	env->wll.drawend += (W_HEIGHT / 2 + env->rot);
	if (env->wll.drawend > W_HEIGHT)
		env->wll.drawend = W_HEIGHT;
	draw_wall(env, x, env->map[env->map_y][env->map_x]);
}

/*
** @desc			pthread core function
** @param arg		copy of env - main game structure
*/

void					*thread_core(void *arg)
{
	t_env	*env;
	int		x;
	int		width;

	env = (t_env *)arg;
	x = (W_WIDTH / 8) * env->nt;
	width = (W_WIDTH / 8) * (env->nt + 1);
	while (x <= width)
	{
		env->cam_x = 2 * x / (float)W_WIDTH - 1;
		env->wll.rdx = env->dir_x + env->wll.plane_x * env->cam_x;
		env->wll.rdy = env->dir_y + env->wll.plane_y * env->cam_x;
		env->map_x = (int)env->pos_x;
		env->map_y = (int)env->pos_y;
		env->wll.ddx = fabs(1 / env->wll.rdx);
		env->wll.ddy = fabs(1 / env->wll.rdy);
		calc_dir(env);
		perform_dda(env, x, env->map[env->map_y][env->map_x]);
		ray_cast(env, x);
		x++;
	}
	return (NULL);
}
