/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:46:53 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/22 14:19:47 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

static void		object_core2(t_env *env, t_sprite *object)
{
	if (object->type == 4 && object->picked == 0)
	{
		env->item_key = 1;
		object->hp -= 100.;
		object->picked = 1;
	}
	if (object->type == 5 && env->item_key == 1)
	{
		env->victory = 1;
		object->hp -= 100.;
		object->picked = 1;
	}
}

void			object_core(t_env *env, t_sprite *object, int i)
{
	if (env->spr.dist[i] <= 0.25)
	{
		if (object->type == 2 && object->picked == 0)
		{
			env->torch = 1;
			object->hp -= 100.;
			object->picked = 1;
		}
		if (object->type == 3 && object->picked == 0)
		{
			env->ammo += 4;
			object->hp -= 100.;
			object->picked = 1;
		}
		object_core2(env, object);
	}
}
