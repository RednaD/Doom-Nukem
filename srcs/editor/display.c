/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:57:36 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/21 23:41:55 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/editor/doomnukem.h"

void	ft_putpixel(t_image image, int x, int y, int color)
{
	int		pos;
	char	*img;

	pos = (image.bpp / 8) * x;
	if (y)
		pos += y * image.size;
	img = image.str;
	img[pos] = (color & 0x0000ff);
	img[pos + 1] = (color & 0x00ff00) >> 8;
	img[pos + 2] = (color & 0xff0000) >> 16;
}

void	ft_copypixel(t_image image_from, t_coord coord_from,
			t_image image_to, t_coord coord_to)
{
	int		pos;

	pos = (image_from.bpp / 8) * coord_from.x;
	pos += coord_from.y * image_from.size;
	return (ft_putpixel(image_to, coord_to.x, coord_to.y,
		*(int*)(&image_from.str[pos])));
}

void	ft_void_point(t_env *env, t_point *point, int pos_x, int pos_y)
{
	int x;
	int y;

	y = -1;
	while (++y < BOX_WIDTH - 1)
	{
		x = -1;
		while (++x < BOX_HEIGHT - 1)
			ft_putpixel(*point->image, x, y, 0);
	}
	point->value = 0;
	mlx_put_image_to_window(env->mlx.mlx_id, env->mlx.window_id,
		point->image->id, (int)(pos_x * (BOX_WIDTH) + 1),
		(int)(pos_y * (BOX_HEIGHT) + 1));
}

void	ft_draw_grid(t_env *env)
{
	int	x;
	int	y;

	env->grid.id = mlx_new_image(env->mlx.mlx_id,
		GRID_WIDTH + 1, GRID_HEIGHT + 1);
	env->grid.str = mlx_get_data_addr(env->grid.id,
		&env->grid.bpp, &env->grid.size, &env->grid.endian);
	x = -1;
	y = -1;
	while (++y <= (GRID_WIDTH))
	{
		x = -1;
		while (++x <= (GRID_HEIGHT))
		{
			if ((x % (BOX_HEIGHT) == 0 || y % (BOX_WIDTH) == 0)
				|| (x == (GRID_HEIGHT) || y == (GRID_WIDTH)))
				ft_putpixel(env->grid, x, y, 0xFFFFFF);
		}
	}
	mlx_put_image_to_window(env->mlx.mlx_id,
		env->mlx.window_id, env->grid.id, 0, 0);
}

void	ft_display_current_texture(t_env *env)
{
	ft_alloc_image(env, &env->texture_display, 64, 64);
	ft_copy_texture(env->current_texture,
		env->texture_display, 64, 64);
	mlx_put_image_to_window(env->mlx.mlx_id,
		env->mlx.window_id, env->texture_display->id, 1400, 700);
}
