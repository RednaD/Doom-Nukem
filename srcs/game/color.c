/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:24:37 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/22 13:58:43 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			transposes hexadecimal color to 3 rgb colors
** @param env		main game structure
** @param color		hexadecimal color value
*/

void			get_rgb_color(t_env *env, int color)
{
	env->color.b = (color & 0x0000ff);
	env->color.g = (color & 0x00ff00) >> 8;
	env->color.r = (color & 0xff0000) >> 16;
}

/*
** @desc			applies fog to wall pixels
** @param env		main game structure
** @param color		hexadecimal color value
*/

void			get_wall_fog(t_env *env, int color)
{
	int t;

	t = (env->torch == -1) ? 4 : 1;
	get_rgb_color(env, color);
	env->color.b *= (env->wll.fog / t);
	env->color.g *= (env->wll.fog / t);
	env->color.r *= (env->wll.fog / t);
}

/*
** @desc			applies fog to floor and ceiling
** @param env		main game structure
** @param color		hexadecimal color value
*/

void			get_floor_or_ceiling_fog(t_env *env, int color, int y)
{
	float	fog;
	int		t;

	t = (env->torch == -1) ? 1200 : 800;
	fog = (1 - ((float)t / abs(y)) / 2.);
	get_rgb_color(env, color);
	env->color.b *= fog;
	env->color.g *= fog;
	env->color.r *= fog;
	env->color.b = (env->color.b < 0 ? 0 : env->color.b);
	env->color.g = (env->color.g < 0 ? 0 : env->color.g);
	env->color.r = (env->color.r < 0 ? 0 : env->color.r);
}

/*
** @desc			applies fog to sprites
** @param env		main game structure
** @param color		hexadecimal color value
** @param dist		sprite distance relative to player
*/

void			get_sprite_fog(t_env *env, int color, float dist)
{
	float	fog;
	int		t;

	t = (env->torch == -1) ? 1 : 8;
	fog = t / dist;
	fog > 1. ? fog = 1. : fog;
	get_rgb_color(env, color);
	env->color.g *= fog;
	env->color.r *= fog;
	env->color.b *= fog;
}
