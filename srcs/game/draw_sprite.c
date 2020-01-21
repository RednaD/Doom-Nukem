/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:05:04 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/22 14:09:24 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			2nd part of sprite computation
** @param env		main game structure
*/

static void		calc_sprite2(t_env *env)
{
	if (env->spr.dsy < 0)
		env->spr.dsy = 0;
	if (env->spr.dsy > W_HEIGHT)
		env->spr.dsy = W_HEIGHT;
	env->spr.dey = env->spr.h / 2;
	env->spr.dey += env->spr.dey * env->pos_z;
	env->spr.dey += (W_HEIGHT / 2 + env->rot);
	if (env->spr.dey > W_HEIGHT)
		env->spr.dey = W_HEIGHT;
	if (env->spr.dey < 0)
		env->spr.dey = 0;
	env->spr.w = abs((int)(W_HEIGHT / (env->spr.trans_y)));
	env->spr.dsx = -env->spr.w / 2 + env->spr.scr_x;
	if (env->spr.dsx < 0)
		env->spr.dsx = 0;
	if (env->spr.dsx > W_WIDTH)
		env->spr.dsx = W_WIDTH;
	env->spr.dex = env->spr.w / 2 + env->spr.scr_x;
	if (env->spr.dex > W_WIDTH)
		env->spr.dex = W_WIDTH;
	if (env->spr.dex < 0)
		env->spr.dex = 0;
}

/*
** @desc			computes sprite datas
** @param env		main game structure
** @param i			sprite index
*/

static void		calc_sprite(t_env *env, int i)
{
	env->spr.x = env->spr.data[i].x - env->pos_x;
	env->spr.y = env->spr.data[i].y - env->pos_y;
	env->spr.inv_det = 1.0 / (env->wll.plane_x * env->dir_y -
		env->dir_x * env->wll.plane_y);
	env->spr.trans_x = env->spr.inv_det *
		(env->dir_y * env->spr.x - env->dir_x * env->spr.y);
	env->spr.trans_y = env->spr.inv_det *
		(-env->wll.plane_y * env->spr.x + env->wll.plane_x * env->spr.y);
	env->spr.scr_x = (int)((W_WIDTH / 2) *
		(1 + env->spr.trans_x / env->spr.trans_y));
	env->spr.h = abs((int)(W_HEIGHT / (env->spr.trans_y)));
	env->spr.dsy = -env->spr.h / 2;
	env->spr.dsy -= env->spr.dsy * env->pos_z;
	env->spr.dsy += W_HEIGHT / 2 + env->rot;
	calc_sprite2(env);
}

/*
** @desc			sorts sprites by distance (painter's algorithm)
** @param env		main game structure
** @param i			sprite index
*/

void			sort_sprite(t_env *env, int i)
{
	float spr_x;
	float spr_y;

	while (i < env->spr.nb_sprite)
	{
		env->spr.order[i] = i;
		spr_x = env->pos_x - env->spr.data[i].x;
		spr_y = env->pos_y - env->spr.data[i].y;
		env->spr.dist[i] = (spr_x * spr_x + spr_y * spr_y);
		i++;
	}
	comb_sort(env->spr.order, env->spr.dist, env->spr.nb_sprite);
}

/*
** @desc			sprites raycast loop
** @param env		main game structure
** @param i			sprite index
*/

static void		draw_sprite_loop(t_env *env, int s, int i)
{
	int	y;
	int color;
	int angle;

	env->spr.tex_x = (int)((env->spr.stripe -
					(-env->spr.w / 2 + env->spr.scr_x)) * 64 / env->spr.w);
	if (env->spr.trans_y > 0 && env->spr.stripe > 0 && env->spr.stripe < W_WIDTH
		&& env->spr.trans_y < env->spr.zbuffer[env->spr.stripe])
	{
		y = env->spr.dsy;
		while (y < env->spr.dey)
		{
			env->spr.tex_y = (y - W_HEIGHT / 2 + (env->spr.h / 2) *
				(-env->pos_z + 1) - env->rot) * 64 / env->spr.h;
			angle = 0;
			if (env->spr.data[s].multi && env->spr.data[s].type == 6)
				angle = get_texture(env);
			color = *(int*)(&env->text_spr[env->spr.data[s].text + angle].str[
			env->spr.tex_y * env->text_spr[env->spr.data[s].text + angle].w +
			env->spr.tex_x]);
			get_sprite_fog(env, color, env->spr.dist[i]);
			pixel_put_sprites(env, color, y, s);
			y++;
		}
	}
}

/*
** @desc			main entry point for sprites rendering
** @param env		main game structure
*/

void			draw_sprite(t_env *env)
{
	int i;

	sort_sprite(env, 0);
	i = -1;
	while (++i < env->spr.nb_sprite)
	{
		if (env->spr.dist[i] < 230)
		{
			calc_sprite(env, env->spr.order[i]);
			if (env->spr.data[env->spr.order[i]].type == 1)
				enemy_core(env, &env->spr.data[env->spr.order[i]],
				env->spr.order[i], i);
			if (env->spr.data[env->spr.order[i]].type >= 2)
				object_core(env, &env->spr.data[env->spr.order[i]], i);
			env->spr.stripe = env->spr.dsx;
			while (env->spr.stripe < env->spr.dex)
			{
				draw_sprite_loop(env, env->spr.order[i], i);
				env->spr.stripe++;
			}
		}
	}
}
