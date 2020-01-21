/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 13:32:42 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/22 02:13:19 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/editor/doomnukem.h"
#include <unistd.h>

int		main(int argc, char *argv[])
{
	t_env	*env;

	env = NULL;
	if (argc != 2)
		ft_throw_error(env, "usage: editor source_file.dn");
	ft_init_env((env = ft_malloc_or_throw(env, sizeof(t_env))));
	ft_check_file(env, argv[1]);
	ft_init_window(env);
	ft_init_texture(env, &env->spawn_texture, NULL, SPAWN_ID);
	ft_init_texture(env, &env->end_texture, "chest.xpm", END_ID);
	ft_load_textures(env);
	if (env->wall_texture == NULL || env->sprite_texture == NULL)
		ft_throw_error(env, "Missing textures.");
	env->current_texture = env->wall_texture;
	if (access(env->file, F_OK) != -1)
		ft_import(env, env->file);
	ft_display_current_texture(env);
	ft_display_life(env);
	ft_display_sky_mode_checkbox(env, &env->sky_mode_display_1,
		env->sky_mode == SKY_MODE_OPEN, (t_coord){CHECKBOX1_X, CHECKBOX1_Y});
	ft_display_sky_mode_checkbox(env, &env->sky_mode_display_2,
		env->sky_mode == SKY_MODE_CLOSED, (t_coord){CHECKBOX2_X, CHECKBOX2_Y});
	ft_init_text(env);
	ft_init_hooks(env);
	return (0);
}

void	ft_exit(t_env *env, int exitcode)
{
	t_coord	coord;

	if (!env)
		return (exit(exitcode));
	coord.y = -1;
	while (++coord.y < BOX_COUNT)
	{
		coord.x = -1;
		while (++coord.x < BOX_COUNT)
			ft_free_image(env, env->points[coord.y][coord.x].image);
	}
	ft_free_image(env, env->texture_display);
	ft_free_image(env, env->sky_mode_display_1);
	ft_free_image(env, env->sky_mode_display_2);
	ft_free_image(env, env->life_level_display);
	if (env->hud)
		ft_free_image(env, env->hud->image);
	free(env->hud);
	ft_free_textures(env, env->spawn_texture);
	ft_free_textures(env, env->wall_texture);
	ft_free_textures(env, env->sprite_texture);
	if (env->mlx.mlx_id && env->mlx.window_id)
		mlx_destroy_window(env->mlx.mlx_id, env->mlx.window_id);
	return (exit(exitcode));
}

void	ft_throw_error(t_env *env, char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	ft_exit(env, 1);
}

void	*ft_malloc_or_throw(t_env *env, int size)
{
	void	*res;

	res = malloc(size);
	if (res == NULL)
		ft_throw_error(env, "Unable to allocate data.");
	return (res);
}

void	ft_load_textures(t_env *env)
{
	ft_load_texture(env, 1, "wall_1.xpm", WALL_MODE);
	ft_load_texture(env, 2, "wall_2.xpm", WALL_MODE);
	ft_load_texture(env, 3, "wall_3.xpm", WALL_MODE);
	ft_load_texture(env, 4, "wall_4.xpm", WALL_MODE);
	ft_load_texture(env, 7, "glass.xpm", WALL_MODE);
	ft_load_texture(env, 8, "door1.xpm", WALL_MODE);
	ft_load_texture(env, 9, "door2.xpm", WALL_MODE);
	ft_load_texture(env, 20, "barrel.xpm", SPRITE_MODE);
	ft_load_texture(env, 40, "mob-front.xpm", SPRITE_MODE);
	ft_load_texture(env, 60, "torch.xpm", SPRITE_MODE);
	ft_load_texture(env, 61, "ammo.xpm", SPRITE_MODE);
	ft_load_texture(env, 62, "key.xpm", SPRITE_MODE);
	ft_load_texture(env, 64, "imp-front.xpm", SPRITE_MODE);
}
