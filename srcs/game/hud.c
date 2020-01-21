/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:38:02 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/22 14:38:29 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

static void				draw_percent(t_env *env, int xpos, int ypos,
							int percent)
{
	int		x;
	int		y;
	int		xend;
	t_text	text;

	text = env->text_gui[15];
	y = -1;
	if (percent > 100 || percent < 1)
		percent = 1;
	xend = 192 * percent / 100;
	while (++y < 21)
	{
		x = -1;
		while (++x < xend)
		{
			get_rgb_color(env,
				text.str[y * text.w + x]);
			pixel_put(env, x + xpos + 25, y + ypos + 5, env->color);
		}
	}
}

/*
** @desc			renders the GUI
** @param env		main game structure
*/

void					main_hud(t_env *env)
{
	if (env->hp < 1)
		draw_image(env, env->text_gui[20], 0, 0);
	else if (env->victory == 1)
		draw_image(env, env->text_gui[19], 0, 0);
	else
	{
		draw_percent(env, 15, 10, env->hp);
		draw_percent(env, 15, 45, env->ammo);
		draw_image(env, env->text_gui[17], 15, 10);
		draw_image(env, env->text_gui[16], 15, 45);
		draw_image(env, env->text_gui[11], W_WIDTH / 2, (W_HEIGHT / 2) - 23);
		if (env->torch == 1)
			draw_image(env, env->text_gui[18], W_WIDTH - 75, W_HEIGHT - 125);
		if (env->item_key == 1)
			draw_image(env, env->text_gui[21], W_WIDTH - 75, -25);
		draw_weapon(env, env->text_gui[env->pistol], W_WIDTH / 2 - 135,
					W_HEIGHT - 340);
		if (env->pistol > 0)
			env->pistol--;
	}
}
