/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 13:32:42 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/22 16:03:23 by stsavida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/editor/doomnukem.h"

void	ft_push_texture(t_env *env, t_texture *texture, int mode)
{
	t_texture	*last_texture;
	t_texture	**current_texture;

	current_texture = mode == WALL_MODE ? &env->wall_texture :
		&env->sprite_texture;
	last_texture = *current_texture;
	if (last_texture)
	{
		texture->next = last_texture;
		while (last_texture->next != *current_texture)
			last_texture = last_texture->next;
		texture->previous = last_texture;
		(*current_texture)->previous = texture;
		last_texture->next = texture;
	}
	else
	{
		texture->previous = texture;
		texture->next = texture;
		*current_texture = texture;
	}
}

void	ft_check_file(t_env *env, char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || !ft_strequ(path + (len - ft_strlen(FILE_EXTENSION)),
		FILE_EXTENSION))
		return (ft_throw_error(env, "Invalid file type."));
	env->file = path;
}

void	ft_alloc_image(t_env *env, t_image **image, int width, int height)
{
	if (!(*image))
	{
		(*image) = ft_malloc_or_throw(env, sizeof(t_image));
		(*image)->id = mlx_new_image(env->mlx.mlx_id,
			width, height);
		(*image)->str =
			mlx_get_data_addr((*image)->id,
			&(*image)->bpp, &(*image)->size,
			&(*image)->endian);
	}
}

void	exit_doom(t_env *env, char *err)
{
	return (ft_throw_error(env, err));
}

int		ft_quit(t_env *env)
{
	ft_exit(env, 0);
	return (0);
}
