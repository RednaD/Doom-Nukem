/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_z_axis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 18:07:46 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/17 18:25:09 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			updates player z axis rotation
** @param env		main game structure
*/

void	pitch(t_env *env)
{
	if (env->key.rot_up == 1 && env->rot < (W_HEIGHT / 2))
		env->rot += 20;
	if (env->key.rot_down == 1 && env->rot > (W_HEIGHT / 2) * -1)
		env->rot -= 20;
}

/*
** @desc			updates player vertical movements
** @param env		main game structure
*/

void	vertical(t_env *env)
{
	if (env->fly == -1)
	{
		if (env->jump == 1 && env->pos_z < 0.8)
			env->pos_z += 0.1;
		if (env->key.up == 0 || env->pos_z >= 0.8)
			env->jump = 0;
		if (env->jump == 0 && env->pos_z > 0)
			env->pos_z -= 0.1;
		if (env->sneak == 1 && env->pos_z > -0.8)
			env->pos_z -= 0.1;
		if (env->key.down == 0)
			env->sneak = 0;
		if (env->sneak == 0 && env->pos_z < 0)
			env->pos_z += 0.1;
	}
	else
	{
		if (env->key.up == 1 && env->pos_z < 0.8)
			env->pos_z += 0.1;
		if (env->key.down == 1 && env->pos_z > -0.8)
			env->pos_z -= 0.1;
	}
}
