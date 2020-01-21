/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 19:48:01 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/21 19:55:27 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

static void			init_texture(t_env *env)
{
	int i;

	i = 0;
	while (i < 11)
		env->text_wll[i++].str = NULL;
	i = 0;
	while (i < 22)
		env->text_gui[i++].str = NULL;
	i = 0;
	while (i < 22)
		env->text_spr[i++].str = NULL;
}

void				check_texture_str(t_env *env)
{
	int i;

	init_texture(env);
	get_texture_gui(env);
	get_texture_wall(env);
	get_texture_sprite(env);
	i = 0;
	while (i < 11)
	{
		if (env->text_wll[i++].str == NULL)
			exit_doom(env, "Error2 : texture wall error exiting..", 1);
	}
	i = 0;
	while (i < 22)
	{
		if (env->text_gui[i++].str == NULL)
			exit_doom(env, "Error2 : texture gui error exiting..", 1);
	}
	i = 0;
	while (i < 22)
	{
		if (env->text_spr[i++].str == NULL)
			exit_doom(env, "Error2 : texture sprite error exiting..", 1);
	}
}
