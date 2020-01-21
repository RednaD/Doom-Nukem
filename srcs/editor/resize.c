/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:16:25 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/21 23:38:12 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/editor/doomnukem.h"
#include <math.h>

void	ft_resize_up(t_texture *texture, t_image *image,
	int desired_width, int desired_height)
{
	t_coord coord;
	int		x_ratio;
	int		y_ratio;

	x_ratio = texture->image->width / desired_width;
	y_ratio = texture->image->height / desired_height;
	coord.y = -1;
	while (++coord.y < texture->image->width)
	{
		coord.x = -1;
		while (++coord.x < texture->image->height)
			if (coord.x % x_ratio == 0 && coord.y % y_ratio == 0 &&
				coord.x / x_ratio < desired_height &&
				coord.y / y_ratio < desired_width)
				ft_copypixel(*texture->image->image, coord,
					*image, (t_coord){coord.x / x_ratio, coord.y / y_ratio});
	}
}

void	ft_resize_down(t_texture *texture, t_image *image,
	int desired_width, int desired_height)
{
	t_coord	coord;
	int		right_padding;
	int		left_padding;
	int		top_padding;
	int		bottom_padding;

	right_padding = floor((double)(desired_width) -
		(double)(texture->image->width)) / 2;
	left_padding = texture->image->width + right_padding;
	top_padding = floor((double)(desired_height) -
		(double)(texture->image->height)) / 2;
	bottom_padding = texture->image->height + top_padding;
	coord.y = -1;
	while (++coord.y < desired_width)
	{
		coord.x = -1;
		while (++coord.x < desired_height)
			if ((coord.x <= right_padding || coord.y <= top_padding) ||
				(coord.x >= left_padding || coord.y >= bottom_padding))
				ft_putpixel(*image, coord.x, coord.y, 0x000000);
			else
				ft_copypixel(*texture->image->image,
					(t_coord){coord.x - left_padding, coord.y - top_padding},
					*image, coord);
	}
}

void	ft_convert_int_to_string(t_text xmp, t_image *image)
{
	int x;
	int y;

	y = -1;
	while (++y < xmp.h)
	{
		x = -1;
		while (++x < xmp.w)
			if (xmp.str[y * xmp.w + x] & 0x00FFFFFF)
				ft_putpixel(*image, x, y, xmp.str[y * xmp.w + x]);
	}
	free(xmp.str);
}
