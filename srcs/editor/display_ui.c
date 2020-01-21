/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 13:32:42 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/06 16:03:18 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/editor/doomnukem.h"

void	ft_display_life(t_env *env)
{
	t_coord	coord;
	int		level;

	ft_alloc_image(env, &env->life_level_display, LIFE_LEVEL_WIDTH + 2,
		LIFE_LEVEL_HEIGHT + 2);
	level = LIFE_LEVEL_HEIGHT - (((double)(env->life_level) / 100) *
		LIFE_LEVEL_HEIGHT) + 1;
	coord.y = LIFE_LEVEL_HEIGHT + 2;
	while (--coord.y >= 0)
	{
		coord.x = LIFE_LEVEL_WIDTH + 1;
		ft_putpixel(*env->life_level_display, coord.x, coord.y, 0xFFFFFF);
		while (--coord.x > 0)
			if (coord.y == LIFE_LEVEL_HEIGHT + 1 || coord.y == 0)
				ft_putpixel(*env->life_level_display, coord.x, coord.y,
					0xFFFFFF);
			else
				ft_putpixel(*env->life_level_display, coord.x, coord.y,
					coord.y + 1 > level ? 0xFF0000 : 0x000000);
		ft_putpixel(*env->life_level_display, 0, coord.y, 0xFFFFFF);
	}
	mlx_put_image_to_window(env->mlx.mlx_id,
		env->mlx.window_id, env->life_level_display->id, 1675, 700);
}

void	ft_display_sky_mode_checkbox(t_env *env, t_image **display,
	int checked, t_coord display_coord)
{
	t_image	*image;
	int		color;
	t_coord	coord;

	ft_alloc_image(env, display, CHECKBOX_WH, CHECKBOX_WH);
	image = *display;
	coord.y = -1;
	color = checked ? 0xFFFFFF : 0x000000;
	while (++coord.y < CHECKBOX_WH)
	{
		coord.x = -1;
		while (++coord.x < CHECKBOX_WH)
			if ((coord.x == 0 || coord.y == 0 ||
				coord.x == CHECKBOX_WH - 1 || coord.y == CHECKBOX_WH - 1))
				ft_putpixel(*image, coord.x, coord.y, 0xFFFFFF);
			else
				ft_putpixel(*image, coord.x, coord.y,
					(coord.x == coord.y || coord.x + coord.y == CHECKBOX_WH - 1)
					? color : 0x000000);
	}
	mlx_put_image_to_window(env->mlx.mlx_id,
		env->mlx.window_id, image->id, display_coord.x, display_coord.y);
}
