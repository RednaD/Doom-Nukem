/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 19:28:18 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/20 16:16:03 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			hooks for the keyboard press
** @param hook		keyboard key pressed
** @param env		main game structure
** @return int		0 on success
*/

static void		key_press2(int hook, t_env *env)
{
	if (hook == CTRL_KEY && env->key.down == 0 && (env->pos_z >= -0.8))
	{
		env->key.down = 1;
		env->sneak = 1;
		env->ws = 0.04;
	}
	if (hook == SHIFT_KEY && env->key.down == 0)
		env->ws = 0.08;
	if (hook == E_KEY)
		doors(env, env->pos_x, env->pos_y);
	if (hook == G_KEY)
		env->wll.decal = env->wll.decal == 0 ? 1 : 0;
	if (hook == R_KEY)
		env->ammo = 2;
	if (hook == ESCAPE_KEY && env->gui == -1)
	{
		env->gui *= -1;
		env->btn[0] = 0;
		env->btn[1] = 0;
	}
	else if (hook == ESCAPE_KEY && env->gui == 1)
		exit_doom(env, "GoodBye :D", 0);
}

/*
** @desc			hooks for the keyboard press
** @param hook		keyboard key pressed
** @param env		main game structure
** @return int		0 on success
*/

int				key_press(int hook, t_env *env)
{
	if (hook == KP_MINUS_KEY)
		env->key.rot_down = 1;
	if (hook == KP_PLUS_KEY)
		env->key.rot_up = 1;
	if (hook == UP_ARROW || hook == W_KEY)
		env->key.forward = 1;
	if (hook == DOWN_ARROW || hook == S_KEY)
		env->key.backward = 1;
	if (hook == RIGHT_ARROW || hook == D_KEY)
		env->key.right = 1;
	if (hook == LEFT_ARROW || hook == A_KEY)
		env->key.left = 1;
	if (hook == SPACE_KEY && env->key.up == 0 && (env->pos_z <= 0.8))
	{
		env->key.up = 1;
		env->jump = 1;
	}
	key_press2(hook, env);
	return (0);
}

/*
** @desc			hooks for the keyboard release
** @param hook		keyboard key pressed
** @param env		main game structure
** @return int		0 on success
*/

static void		key_release2(int hook, t_env *env)
{
	if (hook == CTRL_KEY)
	{
		env->key.down = 0;
		env->ws = 0.06;
	}
	if (hook == SHIFT_KEY && env->key.down == 0)
		env->ws = 0.06;
	if (hook == 3)
		env->fly *= -1;
}

/*
** @desc			hooks for the keyboard release
** @param hook		keyboard key pressed
** @param env		main game structure
** @return int		0 on success
*/

int				key_release(int hook, t_env *env)
{
	if (hook == KP_MINUS_KEY)
		env->key.rot_down = -1;
	if (hook == KP_PLUS_KEY)
		env->key.rot_up = -1;
	if (hook == UP_ARROW || hook == W_KEY)
		env->key.forward = -1;
	if (hook == DOWN_ARROW || hook == S_KEY)
		env->key.backward = -1;
	if (hook == RIGHT_ARROW || hook == D_KEY)
		env->key.right = -1;
	if (hook == LEFT_ARROW || hook == A_KEY)
		env->key.left = -1;
	if (hook == SPACE_KEY)
		env->key.up = 0;
	key_release2(hook, env);
	return (0);
}
