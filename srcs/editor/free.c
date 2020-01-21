/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:17:06 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/21 22:35:25 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/editor/doomnukem.h"

void	ft_free_textures(t_env *env, t_texture *texture)
{
	t_texture	*current;
	t_texture	*tmp;

	current = texture;
	if (!current)
		return ;
	while (current->next != texture)
	{
		tmp = current->next;
		ft_free_texture(env, current);
		current = tmp;
	}
	ft_free_texture(env, current);
}

void	ft_free_texture(t_env *env, t_texture *texture)
{
	if (texture->image->width)
	{
		ft_free_image(env, texture->image->image);
		free(texture->image);
	}
	free(texture);
}

void	ft_free_image(t_env *env, t_image *image)
{
	if (!image)
		return ;
	if (image->id && env->mlx.mlx_id)
		mlx_destroy_image(env->mlx.mlx_id, image->id);
	free(image);
}
