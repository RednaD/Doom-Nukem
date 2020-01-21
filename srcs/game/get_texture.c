/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:05:04 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/22 14:39:17 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			get the wall textures from files
** @param env		main game structure
*/

void				get_texture_wall(t_env *env)
{
	env->text_wll[0] = load_xpm(env, "wall_1.xpm");
	env->text_wll[1] = load_xpm(env, "wall_2.xpm");
	env->text_wll[2] = load_xpm(env, "wall_3.xpm");
	env->text_wll[3] = load_xpm(env, "wall_4.xpm");
	env->text_wll[4] = load_xpm(env, "ceil.xpm");
	env->text_wll[5] = load_xpm(env, "floor.xpm");
	env->text_wll[6] = load_xpm(env, "glass.xpm");
	env->text_wll[7] = load_xpm(env, "sky.xpm");
	env->text_wll[8] = load_xpm(env, "door1.xpm");
	env->text_wll[9] = load_xpm(env, "door2.xpm");
	env->text_wll[10] = load_xpm(env, "doomface.xpm");
}

/*
** @desc			gets the gui textures from files
** @param env		main game structure
*/

void				get_texture_gui(t_env *env)
{
	env->text_gui[0] = load_xpm(env, "shotgun.xpm");
	env->text_gui[1] = load_xpm(env, "shotgun2.xpm");
	env->text_gui[2] = load_xpm(env, "shotgun3.xpm");
	env->text_gui[3] = load_xpm(env, "shotgun4.xpm");
	env->text_gui[4] = load_xpm(env, "shotgun5.xpm");
	env->text_gui[5] = load_xpm(env, "shotgun6.xpm");
	env->text_gui[6] = load_xpm(env, "shotgun7.xpm");
	env->text_gui[7] = load_xpm(env, "shotgun8.xpm");
	env->text_gui[8] = load_xpm(env, "shotgun9.xpm");
	env->text_gui[9] = load_xpm(env, "button_on.xpm");
	env->text_gui[10] = load_xpm(env, "button_off.xpm");
	env->text_gui[11] = load_xpm(env, "crosshair.xpm");
	env->text_gui[12] = load_xpm(env, "title.xpm");
	env->text_gui[13] = load_xpm(env, "menu.xpm");
	env->text_gui[14] = load_xpm(env, "background.xpm");
	env->text_gui[15] = load_xpm(env, "bar_filling.xpm");
	env->text_gui[16] = load_xpm(env, "ammo_bar.xpm");
	env->text_gui[17] = load_xpm(env, "life_bar.xpm");
	env->text_gui[18] = load_xpm(env, "torch.xpm");
	env->text_gui[19] = load_xpm(env, "victory.xpm");
	env->text_gui[20] = load_xpm(env, "gameover.xpm");
	env->text_gui[21] = load_xpm(env, "key_gui.xpm");
}

/*
** @desc			gets the sprite textures from files
** @param env		main game structure
*/

void				get_texture_sprite(t_env *env)
{
	env->text_spr[0] = load_xpm(env, "barrel.xpm");
	env->text_spr[1] = load_xpm(env, "mob-front.xpm");
	env->text_spr[2] = load_xpm(env, "mob-l-2.xpm");
	env->text_spr[3] = load_xpm(env, "mob-r-2.xpm");
	env->text_spr[4] = load_xpm(env, "mob-back.xpm");
	env->text_spr[5] = load_xpm(env, "mob_anim1.xpm");
	env->text_spr[6] = load_xpm(env, "mob_anim2.xpm");
	env->text_spr[7] = load_xpm(env, "mob_anim3.xpm");
	env->text_spr[8] = load_xpm(env, "mob_anim4.xpm");
	env->text_spr[9] = load_xpm(env, "mob_death_anim1.xpm");
	env->text_spr[10] = load_xpm(env, "mob_death_anim2.xpm");
	env->text_spr[11] = load_xpm(env, "mob_death_anim3.xpm");
	env->text_spr[12] = load_xpm(env, "mob_death_anim4.xpm");
	env->text_spr[13] = load_xpm(env, "mob_death_anim5.xpm");
	env->text_spr[14] = load_xpm(env, "item_torch.xpm");
	env->text_spr[15] = load_xpm(env, "ammo.xpm");
	env->text_spr[16] = load_xpm(env, "key.xpm");
	env->text_spr[17] = load_xpm(env, "chest.xpm");
	env->text_spr[18] = load_xpm(env, "imp-front.xpm");
	env->text_spr[19] = load_xpm(env, "imp-right.xpm");
	env->text_spr[20] = load_xpm(env, "imp-left.xpm");
	env->text_spr[21] = load_xpm(env, "imp-back.xpm");
}
