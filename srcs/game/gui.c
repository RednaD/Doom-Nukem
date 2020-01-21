/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:38:02 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/22 14:15:03 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

static void				draw_mission_str2(t_env *env)
{
	if (env->n_gui_str == 4 && env->gui == -1)
		mlx_string_put(env->mlx_ptr, env->win_ptr, (W_WIDTH / 2) - 170,
			(W_HEIGHT / 2) - 270, 0xFFFF00, T5);
	if (env->n_gui_str == 5 && env->gui == -1)
		mlx_string_put(env->mlx_ptr, env->win_ptr, (W_WIDTH / 2) - 170,
			(W_HEIGHT / 2) - 270, 0xFFFF00, T6);
	if (env->n_gui_str == 6 && env->gui == -1)
		mlx_string_put(env->mlx_ptr, env->win_ptr, (W_WIDTH / 2) - 170,
			(W_HEIGHT / 2) - 270, 0xFFFF00, T7);
	if (env->n_gui_str == 7 && env->gui == -1)
		mlx_string_put(env->mlx_ptr, env->win_ptr, (W_WIDTH / 2) - 170,
			(W_HEIGHT / 2) - 270, 0xFFFF00, T8);
}

static void				draw_mission_str(t_env *env)
{
	if (env->state == 1 && env->gui == -1 && env->n_gui_str < 8)
	{
		env->count_s++;
		if ((env->count_s % 60 == 0) && (env->count_s / 60) % 4 == 0)
			env->n_gui_str++;
	}
	if (env->n_gui_str == 0 && env->gui == -1)
		mlx_string_put(env->mlx_ptr, env->win_ptr, (W_WIDTH / 2) - 170,
			(W_HEIGHT / 2) - 270, 0xFFFF00, T1);
	if (env->n_gui_str == 1 && env->gui == -1)
		mlx_string_put(env->mlx_ptr, env->win_ptr, (W_WIDTH / 2) - 170,
			(W_HEIGHT / 2) - 270, 0xFFFF00, T2);
	if (env->n_gui_str == 2 && env->gui == -1)
		mlx_string_put(env->mlx_ptr, env->win_ptr, (W_WIDTH / 2) - 170,
			(W_HEIGHT / 2) - 270, 0xFFFF00, T3);
	if (env->n_gui_str == 3 && env->gui == -1)
		mlx_string_put(env->mlx_ptr, env->win_ptr, (W_WIDTH / 2) - 170,
			(W_HEIGHT / 2) - 270, 0xFFFF00, T4);
	draw_mission_str2(env);
}

void					draw_main_menu_str(t_env *env)
{
	int color[2];
	int i;

	mlx_mouse_show();
	if (env->gui == 1)
	{
		i = -1;
		while (++i < 2)
		{
			if (env->btn[i] == 1)
				color[i] = 0xFFFF00;
			else
				color[i] = 0xFFFFFF;
		}
		if (env->state == 0)
			mlx_string_put(env->mlx_ptr, env->win_ptr, (W_WIDTH / 2) - 50,
				(W_HEIGHT / 2) + 100, color[0], "START GAME");
		else
			mlx_string_put(env->mlx_ptr, env->win_ptr, (W_WIDTH / 2) - 55,
				(W_HEIGHT / 2) + 100, color[0], "RESUME GAME");
		mlx_string_put(env->mlx_ptr, env->win_ptr, (W_WIDTH / 2) - 45,
			(W_HEIGHT / 2) + 195, color[1], "EXIT GAME");
	}
	if (env->hp > 0 && env->victory != 1)
		draw_mission_str(env);
}

static void				draw_main_menu(t_env *env)
{
	draw_image(env, env->text_gui[14], 0, 0);
	draw_image(env, env->text_gui[12], (W_WIDTH / 2) - 434,
		(W_HEIGHT / 2) - 200);
	draw_image(env, env->text_gui[13], (W_WIDTH / 2) - 126,
		(W_HEIGHT / 2) + 50);
	if (env->btn[0] == 1)
		draw_image(env, env->text_gui[9], (W_WIDTH / 2) - 81,
			(W_HEIGHT / 2) + 75);
	else
		draw_image(env, env->text_gui[10], (W_WIDTH / 2) - 81,
			(W_HEIGHT / 2) + 75);
	if (env->btn[1] == 1)
		draw_image(env, env->text_gui[9], (W_WIDTH / 2) - 81,
			(W_HEIGHT / 2) + 170);
	else
		draw_image(env, env->text_gui[10], (W_WIDTH / 2) - 81,
			(W_HEIGHT / 2) + 170);
}

/*
** @desc			renders the GUI
** @param env		main game structure
*/

void					main_gui(t_env *env)
{
	if (env->gui == -1)
		main_hud(env);
	else
		draw_main_menu(env);
}
