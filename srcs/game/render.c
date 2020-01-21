/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 03:35:01 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/22 14:53:08 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

/*
** @desc			gets clock time after gamestate has been refreshed
** @param env		main game structure
*/

void				get_clock_time(t_env *env)
{
	env->gl.currclock = clock();
	env->gl.frameclock = env->gl.currclock - env->gl.prevclock;
	if (env->gl.frameclock < CLOCKS_PER_SEC)
		sleep((float)(CLOCKS_PER_SEC - env->gl.frameclock) /
				CLOCKS_PER_SEC / 10.0);
	env->gl.prevclock = env->gl.currclock;
}

/*
** @desc			refreshes the gamestate (called in loop)
** @param env		main game structure
** @return int		0 on success
*/

int					redraw(t_env *env)
{
	mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	env->img_ptr = NULL;
	if (!(env->img_ptr = mlx_new_image(env->mlx_ptr, W_WIDTH, W_HEIGHT)))
		exit_doom(env, "Error : malloc error exiting..", 1);
	env->img_str = mlx_get_data_addr(env->img_ptr, &(env->bpp),
		&(env->size_line), &(env->endian));
	if (env->gui == -1 && env->hp > 0 && env->victory != 1)
	{
		render(env);
		move_handler(env);
		mlx_mouse_move(env->win_ptr, W_WIDTH / 2, W_HEIGHT / 2);
		mlx_mouse_hide();
	}
	main_gui(env);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
	draw_main_menu_str(env);
	get_clock_time(env);
	return (0);
}

/*
** @desc			puts pixel onto the screen buffer
** @param env		main game structure
** @param x, y		screen pixel coordinates
** @param color		rgb color to write onto the screen buffer
*/

void				pixel_put(t_env *env, int x, int y, t_color color)
{
	if (x >= W_WIDTH || y >= W_HEIGHT || x < 0 || y < 0)
		return ;
	env->img_str[((env->bpp / 8) * x) + (env->size_line * y)
		+ 0] = (char)color.b;
	env->img_str[((env->bpp / 8) * x) + (env->size_line * y)
		+ 1] = (char)color.g;
	env->img_str[((env->bpp / 8) * x) + (env->size_line * y)
		+ 2] = (char)color.r;
}

/*
** @desc			main rendering function
** @param env		main game structure
*/

void				render(t_env *env)
{
	pthread_t		thread[8];
	t_env			env_thread[8];

	if (env->state == 0)
		system("/usr/bin/afplay snd/background.mp3 > /dev/null 2>&1 &");
	env->state = 1;
	env->nt = 0;
	while (env->nt < 8)
	{
		ft_memcpy((void*)&env_thread[env->nt], (void*)env, sizeof(t_env));
		env_thread[env->nt].core = env;
		pthread_create(&thread[env->nt], NULL, thread_core,
			&env_thread[env->nt]);
		env->nt++;
	}
	while (env->nt--)
		pthread_join(thread[env->nt], NULL);
	draw_sprite(env);
}
