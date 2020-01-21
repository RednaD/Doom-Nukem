/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:21:43 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/22 14:15:32 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			hooks for the mouse buttons
** @param button	mouse button
** @param x, y		x, y screen pixel coordinates
** @param env		main game structure
** @return int		0 on success
*/

int		mouse_button_press(int button, int x, int y, t_env *env)
{
	if (env->btn[0] == 1 && button == 1 && env->gui == 1)
	{
		mlx_mouse_hide();
		mlx_mouse_move(env->win_ptr, W_WIDTH / 2, W_HEIGHT / 2);
		env->gui = -1;
	}
	else if (env->btn[1] == 1 && button == 1 && env->gui == 1)
		exit_doom(env, "GoodBye :D", 0);
	else if (((button == 1 && env->pistol == 0) &&
		x < W_WIDTH && y < W_HEIGHT) && env->gui == -1 &&
		env->hp > 0 && env->victory != 1)
	{
		if (env->ammo > 1)
		{
			system("/usr/bin/afplay snd/gun_1.wav > /dev/null 2>&1 &");
			env->firing = 1;
			env->ammo--;
			env->pistol = 3;
		}
		system("/usr/bin/afplay snd/gun_2.wav > /dev/null 2>&1 &");
	}
	return (0);
}

int		mouse_button_release(int button, int x, int y, t_env *env)
{
	if ((button == 1 && x < W_WIDTH && y < W_HEIGHT) && env->gui == -1)
		env->firing = 0;
	return (0);
}

/*
** @desc			hooks for the mouse motion
** @param x, y		x, y screen pixel coordinates
** @param env		main game structure
** @return int		0 on success
*/

int		mouse_motion(int x, int y, t_env *env)
{
	if (env->gui == -1)
	{
		env->rs = (0.005) * (x - W_WIDTH / 2);
		env->rot -= (y - W_HEIGHT / 2);
		if (env->rot < (W_HEIGHT / 2) * -1)
			env->rot = (W_HEIGHT / 2) * -1;
		if (env->rot > W_HEIGHT / 2)
			env->rot = W_HEIGHT / 2;
	}
	if (env->gui == 1)
	{
		if (((x >= 433 && x <= 594) && (y >= 437 && y <= 510)))
			env->btn[0] = 1;
		else
			env->btn[0] = 0;
		if (((x >= 433 && x <= 594) && (y >= 507 && y <= 605)))
			env->btn[1] = 1;
		else
			env->btn[1] = 0;
	}
	return (0);
}
