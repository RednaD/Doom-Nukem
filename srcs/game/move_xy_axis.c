/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_xy_axis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:13:31 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/21 21:20:20 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <math.h>

/*
** @desc			updates forward and backward player movements
** @param env		main game structure
*/

static void	move_forward_backward(t_env *env)
{
	if (env->key.forward == 1)
	{
		if (env->map[(int)(env->pos_y)][(int)(env->pos_x + env->dir_x *
				env->ws)] <= 0)
			env->pos_x += env->dir_x * env->ws;
		if (env->map[(int)(env->pos_y + env->dir_y * env->ws)]
				[(int)(env->pos_x)] <= 0)
			env->pos_y += env->dir_y * env->ws;
	}
	if (env->key.backward == 1)
	{
		if (env->map[(int)(env->pos_y)][(int)(env->pos_x - env->dir_x *
				env->ws)] <= 0)
			env->pos_x -= env->dir_x * env->ws;
		if (env->map[(int)(env->pos_y - env->dir_y * env->ws)]
				[(int)(env->pos_x)] <= 0)
			env->pos_y -= env->dir_y * env->ws;
	}
}

/*
** @desc			updates right and left player movements
** @param env		main game structure
*/

static void	move_right_left(t_env *env)
{
	if (env->key.right == 1)
	{
		if (env->map[(int)(env->pos_y)][(int)(env->pos_x - env->dir_y *
				env->ws)] <= 0)
			env->pos_x -= (env->dir_y) * env->ws;
		if (env->map[(int)(env->pos_y + env->dir_x * env->ws)]
				[(int)(env->pos_x)] <= 0)
			env->pos_y += (env->dir_x) * env->ws;
	}
	if (env->key.left == 1)
	{
		if (env->map[(int)(env->pos_y)][(int)(env->pos_x + env->dir_y *
				env->ws)] <= 0)
			env->pos_x += (env->dir_y) * env->ws;
		if (env->map[(int)(env->pos_y - env->dir_x * env->ws)]
				[(int)(env->pos_x)] <= 0)
			env->pos_y -= (env->dir_x) * env->ws;
	}
}

/*
** @desc			updates player xy axis rotation
** @param env		main game structure
*/

static void	rotation(t_env *env)
{
	float tmp;

	if (env->key.rot_right == 1)
		env->rs = 0.2 * -1;
	if (env->key.rot_left == 1)
		env->rs = 0.2;
	tmp = env->dir_x;
	env->dir_x = env->dir_x * cos(env->rs) - env->dir_y * sin(env->rs);
	env->dir_y = tmp * sin(env->rs) + env->dir_y * cos(env->rs);
	tmp = env->wll.plane_x;
	env->wll.plane_x = env->wll.plane_x * cos(env->rs) - env->wll.plane_y
		* sin(env->rs);
	env->wll.plane_y = tmp * sin(env->rs) + env->wll.plane_y * cos(env->rs);
	env->rs = 0;
}

/*
** @desc			handles player movements updates
** @param env		main game structure
*/

void		move_handler(t_env *env)
{
	vertical(env);
	move_forward_backward(env);
	move_right_left(env);
	rotation(env);
	pitch(env);
}
