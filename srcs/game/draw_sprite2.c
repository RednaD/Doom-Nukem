/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:09:09 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/22 14:09:48 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			gets different texture depending on the player's direction
** @param env		main game structure
*/

int				get_texture(t_env *env)
{
	if (env->spr.x <= 0 && env->spr.y <= 0)
		return (0);
	else if (env->spr.x >= 0 && env->spr.y <= 0)
		return (1);
	else if (env->spr.x <= 0 && env->spr.y >= 0)
		return (2);
	else if (env->spr.x >= 0 && env->spr.y >= 0)
		return (3);
	return (0);
}

void			pixel_put_sprites(t_env *env, int color, int y, int s)
{
	if (env->spr.data[s].type == 1)
	{
		if (color & 0xFFFF0000 || color == 0)
			pixel_put(env, env->spr.stripe, y, env->color);
	}
	else if (env->spr.data[s].type == 0)
	{
		if (color & 0xFFFFFF)
			pixel_put(env, env->spr.stripe, y, env->color);
	}
	else if (env->spr.data[s].type >= 2 && env->spr.data[s].hp > 0)
	{
		if (color & 0xFFFF0000 || color == 0)
			pixel_put(env, env->spr.stripe, y, env->color);
	}
}
