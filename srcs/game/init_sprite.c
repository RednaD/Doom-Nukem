/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 04:02:11 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/21 21:19:54 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			initializes start value for enemy sprites
** @param spr		sprite structure
** @param value		value parsed from the map file
** of the range of loaded textures for the enemies
*/

static void		create_enemy_sprite(t_sprite *spr, int value)
{
	if (40 <= value && value <= 59)
	{
		spr->text = value - 40 + 2;
		spr->type = 1;
		spr->hp = 60;
		spr->multi = 1;
		spr->anim = 0;
	}
}

/*
** @desc			initializes start value for pickup sprites
** @param spr		sprite structure
** @param value		value parsed from the map file
** of the range of loaded textures for the enemies
*/

static void		create_obj_sprite(t_sprite *spr, int value)
{
	if (60 <= value && value <= 79)
	{
		spr->text = value - 60 + 14;
		spr->hp = 100.;
		spr->picked = 0;
		if (value == 60)
			spr->type = 2;
		if (value == 61)
			spr->type = 3;
		if (value == 62)
			spr->type = 4;
		if (value == 63)
			spr->type = 5;
		if (value == 64)
		{
			spr->type = 6;
			spr->multi = 1;
		}
	}
}

/*
** @desc			initializes start value for decoration sprites
** @param spr		sprite structure
** @param value		value parsed from the map file
** of the range of loaded textures for the enemies
*/

static void		create_env_sprite(t_sprite *spr, int value)
{
	if (20 <= value && value <= 39)
	{
		spr->text = value - 20;
		spr->type = 0;
		spr->hp = -1;
		spr->multi = 0;
	}
}

/*
** @desc			initializes start value for a sprite
** @param spr		sprite structure
** @param x, y		map coordinates
** @param value		value parsed from the map file
** @misc			type 0 is for decoration sprites
** @misc			type 1 is for enemy sprites
** @misc			type 2 is for pickup objects
** of the range of loaded textures for the enemies
*/

void			create_sprites(t_sprite *spr, float x, float y, int value)
{
	spr->x = x;
	spr->y = y;
	create_env_sprite(spr, value);
	create_enemy_sprite(spr, value);
	create_obj_sprite(spr, value);
	spr->death_anim = 0;
}

/*
** @desc			initializes sprites given map data
** @param env		main game structure
** @param x, y		map coordinates
** @param i			sprite index
*/

void			init_sprites(t_env *env, int x, int y, int *i)
{
	int map_value;

	map_value = env->map[y][x];
	if (20 <= env->map[y][x] && env->map[y][x] <= 79)
	{
		env->spr.nb_sprite++;
		if (40 <= env->map[y][x] && env->map[y][x] <= 79)
			env->map[y][x] = 0;
		create_sprites(&env->spr.data[*i], (float)x + 0.5, (float)y + 0.5,
			map_value);
		(*i)++;
	}
}
