/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:43:32 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/22 01:30:41 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <unistd.h>

/*
** @desc			destroys the buffers used by the mlx framework
** @param env		main game structure
*/

static void				clear_mlx(t_env *env)
{
	int y;

	y = 0;
	while (y < 11 && env->text_wll[y].str != NULL)
		free(env->text_wll[y++].str);
	y = 0;
	while (y < 22 && env->text_gui[y].str != NULL)
		free(env->text_gui[y++].str);
	y = 0;
	while (y < 22 && env->text_spr[y].str != NULL)
		free(env->text_spr[y++].str);
	if (env->img_ptr != NULL)
		mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	if (env->mlx_ptr != NULL && env->img_ptr != NULL)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
}

/*
** @desc			frees memory at program exit
** @param env		main game structure
** @param str		message to be displayed on exit
** @param e			error signal number
*/

void					exit_doom(t_env *env, char *str, int e)
{
	int y;

	y = 0;
	ft_putendl_fd(str, e + 1);
	y = 0;
	if (env->fd == -1)
		close(env->fd);
	clear_mlx(env);
	system("/usr/bin/killall afplay 2&>/dev/null >/dev/null");
	exit(e);
}
