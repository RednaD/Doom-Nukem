/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 18:09:15 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/21 21:15:54 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

void	decal(t_env *env)
{
	if (env->wll.tex_x >= 20 && env->wll.tex_x <= 44 && env->wll.tex_y >= 20 &&
			env->wll.tex_y <= 44 &&
			env->map[env->map_y][env->map_x] < 7 &&
			env->wll.tex_y >= 0 &&
			((env->wll.side == 0 &&
			env->wll.rdx < 0 &&
			env->map[env->map_y][env->map_x + 1] >= 0) ||
			(env->wll.side == 0 &&
			env->wll.rdx > 0 &&
			env->map[env->map_y][env->map_x - 1] >= 0) ||
			(env->wll.side == 1 &&
			env->wll.rdy < 0 &&
			env->map[env->map_y + 1][env->map_x] >= 0) ||
			(env->wll.side == 1 &&
			env->wll.rdy > 0 &&
			env->map[env->map_y - 1][env->map_x] >= 0)))
		env->wll.tex_i = 10;
}
