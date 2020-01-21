/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:59:54 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/15 17:12:19 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/editor/doomnukem.h"
#include <math.h>

int		ft_onmouseclick(int button, int x, int y, t_env *env)
{
	t_point	*point;

	ft_checkbox_onmouseclick(button, x, y, env);
	if (x < 0 || y < 0)
		return (0);
	x = floor((double)x / (double)(BOX_WIDTH));
	y = floor((double)y / (double)(BOX_HEIGHT));
	if (x > (BOX_COUNT - 1) || y > (BOX_COUNT - 1))
		return (0);
	point = &(env->points[y][x]);
	if (button == MOUSE_RIGHT_CLICK && point->image->id)
	{
		if (point->value == SPAWN_ID)
			env->spawn_placed = 0;
		ft_void_point(env, point, x, y);
	}
	else if (button == MOUSE_LEFT_CLICK)
		if (env->current_mode != SPAWN_MODE || !env->spawn_placed)
		{
			if (env->current_mode == SPAWN_MODE || point->value == SPAWN_ID)
				env->spawn_placed = env->current_mode == SPAWN_MODE;
			ft_put_texture(env, x, y, env->current_texture);
		}
	return (0);
}

int		ft_onkeypress(int keycode, t_env *env)
{
	if (keycode == KEYCODE_S)
	{
		ft_export(env, env->file);
		ft_exit(env, 0);
	}
	else if (keycode == KEYCODE_ESC)
		ft_exit(env, 0);
	else if (keycode == KEYCODE_P)
		ft_swap_mode(env,
			env->current_mode == SPAWN_MODE ? WALL_MODE : SPAWN_MODE);
	else if (keycode == KEYCODE_E)
		ft_swap_mode(env,
			env->current_mode == END_MODE ? WALL_MODE : END_MODE);
	else if (keycode == KEYCODE_M)
		ft_swap_mode(env,
			env->current_mode == WALL_MODE ? SPRITE_MODE : WALL_MODE);
	else if (keycode == KEYCODE_LEFT_ARROW || keycode == KEYCODE_RIGHT_ARROW)
	{
		if (keycode == KEYCODE_LEFT_ARROW)
			env->current_texture = env->current_texture->previous;
		else
			env->current_texture = env->current_texture->next;
		ft_display_current_texture(env);
	}
	return (1);
}

int		ft_onkeypressl(int keycode, t_env *env)
{
	if (keycode == KEYCODE_UP_ARROW || keycode == KEYCODE_DOWN_ARROW)
	{
		if (keycode == KEYCODE_UP_ARROW)
			env->life_level++;
		else
			env->life_level--;
		if (env->life_level > 100)
			env->life_level = 100;
		else if (env->life_level < 1)
			env->life_level = 1;
		ft_display_life(env);
	}
	return (1);
}

void	ft_swap_mode(t_env *env, int mode)
{
	if (mode == SPAWN_MODE)
		env->current_texture = env->spawn_texture;
	else if (mode == END_MODE)
		env->current_texture = env->end_texture;
	else if (mode == WALL_MODE)
		env->current_texture = env->wall_texture;
	else if (mode == SPRITE_MODE)
		env->current_texture = env->sprite_texture;
	env->current_mode = mode;
	ft_display_current_texture(env);
}

int		ft_checkbox_onmouseclick(int button, int x, int y, t_env *env)
{
	if (button != MOUSE_LEFT_CLICK)
		return (0);
	if (x >= CHECKBOX1_X && x <= CHECKBOX1_X + CHECKBOX_WH &&
		y >= CHECKBOX1_Y && y <= CHECKBOX1_Y + CHECKBOX_WH)
		env->sky_mode = SKY_MODE_OPEN;
	else if (x >= CHECKBOX2_X && x <= CHECKBOX2_X + CHECKBOX_WH &&
		y >= CHECKBOX2_Y && y <= CHECKBOX2_Y + CHECKBOX_WH)
		env->sky_mode = SKY_MODE_CLOSED;
	else
		return (0);
	ft_display_sky_mode_checkbox(env, &env->sky_mode_display_1,
		env->sky_mode == SKY_MODE_OPEN, (t_coord){CHECKBOX1_X, CHECKBOX1_Y});
	ft_display_sky_mode_checkbox(env, &env->sky_mode_display_2,
		env->sky_mode == SKY_MODE_CLOSED, (t_coord){CHECKBOX2_X, CHECKBOX2_Y});
	return (0);
}
