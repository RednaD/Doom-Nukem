/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 18:18:15 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/22 15:51:16 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

static void		get_enemy_texture(t_sprite *enemy, float dist)
{
	int m;

	m = 20;
	if (enemy->type == 1 && enemy->hp > 0 && dist <= 30)
	{
		5 < enemy->anim % m ? enemy->text = 5 : 0;
		(5 <= enemy->anim % m && enemy->anim % m < 10) ? enemy->text = 6 : 0;
		(10 <= enemy->anim % m && enemy->anim % m < 15) ? enemy->text = 7 : 0;
		(15 <= enemy->anim % m && enemy->anim % m < 20) ? enemy->text = 8 : 0;
	}
	m = 25;
	if (enemy->type == 1 && enemy->hp <= 0 && enemy->anim < 25)
	{
		enemy->anim % m < 5 ? enemy->text = 9 : 0;
		(5 <= enemy->anim % m && enemy->anim % m < 10) ? enemy->text = 10 : 0;
		(10 <= enemy->anim % m && enemy->anim % m < 15) ? enemy->text = 11 : 0;
		(15 <= enemy->anim % m && enemy->anim % m < 20) ? enemy->text = 12 : 0;
		(20 <= enemy->anim % m && enemy->anim % m < 25) ? enemy->text = 13 : 0;
	}
	if (enemy->type == 1 && enemy->hp > 0 && dist > 30)
		enemy->text = 1;
}

static void		get_enemy_collision_with_map(t_env *env, t_sprite *enemy,
		int *map)
{
	map[0] = env->map[(int)(enemy->y)][(int)(enemy->x + 0.3)];
	map[1] = env->map[(int)(enemy->y)][(int)(enemy->x - 0.3)];
	map[2] = env->map[(int)(enemy->y + 0.3)][(int)(enemy->x)];
	map[3] = env->map[(int)(enemy->y - 0.3)][(int)(enemy->x)];
}

static void		enemy_movement(t_env *env, t_sprite *enemy, int i)
{
	int map[4];

	get_enemy_collision_with_map(env, enemy, map);
	if (env->pos_x + 0.5 > enemy->x &&
			(map[0] <= 0 || (40 <= map[0] && map[0] <= 59)))
		enemy->x += 0.02;
	if (env->pos_x - 0.5 < enemy->x &&
			(map[1] <= 0 || (40 <= map[1] && map[1] <= 59)))
		enemy->x -= 0.02;
	if (env->pos_y + 0.5 > enemy->y &&
			(map[2] <= 0 || (40 <= map[2] && map[2] <= 59)))
		enemy->y += 0.02;
	if (env->pos_y - 0.5 < enemy->y &&
			(map[3] <= 0 || (40 <= map[3] && map[3] <= 59)))
		enemy->y -= 0.02;
	if (env->spr.dist[i] <= 0.5)
		env->hp -= 1;
	enemy->anim++;
	enemy->anim > 20 ? enemy->anim = 0 : 0;
}

static void		is_enemy_hit(t_env *env, t_sprite *enemy)
{
	if (env->firing == 1 &&
	enemy->type == 1 && enemy->hp > 0 &&
	W_WIDTH / 2 >= env->spr.dsx &&
	W_WIDTH / 2 <= env->spr.dex &&
	W_HEIGHT / 2 >= env->spr.dsy &&
	W_HEIGHT / 2 <= env->spr.dey &&
	env->spr.trans_y < env->spr.zbuffer[W_WIDTH / 2] &&
	env->spr.trans_y > 0)
		enemy->hp -= 200;
	if (enemy->hp <= 0)
		enemy->anim = 0;
}

void			enemy_core(t_env *env, t_sprite *enemy, int s, int i)
{
	get_enemy_texture(&env->spr.data[s], env->spr.dist[i]);
	if (enemy->type == 1 && enemy->hp > 0)
	{
		if (env->spr.dist[i] <= 30)
		{
			enemy_movement(env, &env->spr.data[s], i);
			is_enemy_hit(env, &env->spr.data[s]);
		}
	}
	if (enemy->type == 1 && enemy->hp <= 0)
		enemy->anim++;
}
