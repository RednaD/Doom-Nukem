/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:39:57 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/22 14:51:15 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <unistd.h>

/*
** @desc			initializes the mlx framework and loads the textures
** @param env		main game structure
*/

static	void			start_doom(t_env *env)
{
	env->mlx_ptr = mlx_init();
	if (env->mlx_ptr == NULL)
		exit_doom(env, "Error : mlx unexpected error exiting..", 1);
	if (!(env->win_ptr = mlx_new_window(env->mlx_ptr, W_WIDTH, W_HEIGHT,
			"Doom-Nukem")))
		exit_doom(env, "Error : mlx unexpected error exiting..", 1);
	if ((env->img_ptr = mlx_new_image(env->mlx_ptr, W_WIDTH, W_HEIGHT)) == NULL)
		exit_doom(env, "Error : malloc error exiting..", 1);
	env->img_str = mlx_get_data_addr(env->img_ptr, &(env->bpp),
			&(env->size_line), &(env->endian));
}

/*
** @desc			allows a clean exit when clicking the red arrow
** @param env		main game structure
** @return int		0 on success
*/

static int				stop_doom(t_env *env)
{
	exit_doom(env, "Bye :D", 0);
	return (0);
}

/*
** @desc			gives info about key bindings to the player
*/

static	void			display_hook(void)
{
	ft_putstr("ESC = Quit\n");
	ft_putstr("UP/W = Move up          | DOWN/S = Move down\n");
	ft_putstr("LEFT/A = Move left      | RIGHT/D = Move right\n");
	ft_putstr("LEFT_CLICK = Shoot      | F = Fly mode\n");
	ft_putstr("SPACE = Jump            | E = Use door\n");
	ft_putstr("SHIFT = Sprint          | CTRL = Crouch\n");
	ft_putstr("G = Posters             | R = Reload\n");
}

/*
** @desc			main entry point to the program
** @param argv		*.dn map file to be specified at launch
** @return int		0 at program exit
*/

int						main(int argc, char **argv)
{
	t_env init_env;
	t_env *env;

	env = &init_env;
	init_struct_core(env);
	if (argc != 2)
		exit_doom(env, "usage: doom-nukem source_file.dn", 1);
	ft_check_file(env, argv[1]);
	if (access(env->file, F_OK) != -1)
		ft_import(env, env->file, 0);
	else
		exit_doom(env, "Unable to load file.", 0);
	check_texture_str(env);
	display_hook();
	start_doom(env);
	env->gl.prevclock = clock();
	mlx_hook(env->win_ptr, 4, 0, mouse_button_press, env);
	mlx_hook(env->win_ptr, 5, 0, mouse_button_release, env);
	mlx_hook(env->win_ptr, CLOSE, (1L << 17), stop_doom, env);
	mlx_hook(env->win_ptr, KEYPRESS, (1L << 0), key_press, env);
	mlx_hook(env->win_ptr, KEYRELEASE, (1L << 1), key_release, env);
	mlx_hook(env->win_ptr, 6, 0, mouse_motion, env);
	mlx_loop_hook(env->mlx_ptr, redraw, env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
