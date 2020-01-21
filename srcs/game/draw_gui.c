/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 03:40:40 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/22 14:01:23 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			renders the GUI
** @param env		main game structure
*/

void				draw_image(t_env *env, t_text text, int xp, int yp)
{
	int x;
	int y;

	y = -1;
	while (++y < text.h)
	{
		x = -1;
		while (++x < text.w)
		{
			get_rgb_color(env, text.str[y * text.w + x]);
			if (text.str[y * text.w + x] & 0x00FFFFFF)
				pixel_put(env, x + xp, y + yp, env->color);
			if ((text.str[y * text.w + x] & 0x00FFFFFF))
				pixel_put(env, x + xp, y + yp, env->color);
		}
	}
}

/*
** @desc			renders the weapon
** @param env		main game structure
** @param text		texture index
** @pos_x, pos_y	x, y screen placement coordinates for the weapon
*/

void				draw_weapon(t_env *env, t_text text, int pos_x, int pos_y)
{
	int x;
	int y;
	int color;

	y = 0;
	while (y < text.h)
	{
		x = 0;
		while (x < text.w)
		{
			color = *(int*)(&text.str[y * text.w + x]);
			get_rgb_color(env, color);
			if (color & 0xFFFF0000 || color == 0)
			{
				pixel_put(env, x + pos_x, y + pos_y, env->color);
			}
			x++;
		}
		y++;
	}
}
