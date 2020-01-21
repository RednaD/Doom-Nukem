/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:05:50 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/22 14:48:21 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <fcntl.h>
#include <unistd.h>

static void		ft_generate_points_from_line2(t_env *env, int x, int y)
{
	env->map[y + 1][x + 1] = 0;
	env->pos_x = x + 0.5 + 1;
	env->pos_y = y + 0.5 + 1;
	env->spawn_placed = 1;
}

/*
** @desc			parses map data and initializes sprites
** @param env		main game structure
** @param line		line of text from map file
** @param y			line index of the map file
*/

static void		ft_generate_points_from_line(t_env *env, char *line, int y)
{
	int			x;
	char		**rm;
	char		**tab;
	int			value;
	static int	i;

	x = -1;
	if (!(tab = ft_strsplit(line, ' ')))
		exit_doom(env, "Unable to load file.", 1);
	rm = tab;
	while (*tab && ++x >= 0)
	{
		if (x == 32)
			exit_doom(env, "Invalid file.", 0);
		value = ft_atoi(*tab);
		if (!env->spawn_placed && value == 100)
			ft_generate_points_from_line2(env, x, y);
		else if (value != 100)
		{
			env->map[y + 1][x + 1] = value;
			init_sprites(env, x + 1, y + 1, &i);
		}
		free(*(tab++));
	}
	free(rm);
}

/*
** @desc			parses map file header
** @param env		main game structure
** @param line		line of text from map file
*/

static void		ft_parse_file_header(t_env *env, char *line)
{
	char	**params;

	params = ft_strsplit(line, ';');
	if (params[2] != 0 || params[0][0] != '#')
		exit_doom(env, "Invalid header on file.", 0);
	env->sky_mode = ft_atoi(params[0] + 1);
	if (env->sky_mode != 1 && env->sky_mode != 2)
		env->sky_mode = 1;
	env->hp = ft_atoi(params[1]);
	if (env->hp > 100)
		env->hp = 100.;
	else if (env->hp < 1)
		env->hp = 1.;
	free(params[0]);
	free(params[1]);
	free(params);
}

/*
** @desc			opens, checks and parses map file
** @param env		main game structure
** @param path		map filepath
*/

void			ft_import(t_env *env, char *path, int y)
{
	int		state;
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (exit_doom(env, "Can't open file.", 1));
	while ((state = get_next_line(fd, &line)) > 0)
	{
		if (y == 0 && line[0] != '#')
			exit_doom(env, "Missing header in file.", 0);
		if (y == 32 + 1)
			exit_doom(env, "Invalid file.", 0);
		if (y == 0 && ++y)
			ft_parse_file_header(env, line);
		else
			ft_generate_points_from_line(env, line, y++ - 1);
		free(line);
	}
	if (state == -1)
		exit_doom(env, "Unable to load file.", 1);
	if (env->pos_x == -1 || env->pos_y == -1)
		exit_doom(env, "Map error", 0);
	close(fd);
}

/*
** @desc			basic map file checks
** @param env		main game structure
** @param path		map filepath
*/

void			ft_check_file(t_env *env, char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || !ft_strequ(path + (len - ft_strlen(".dn")), ".dn"))
		return (exit_doom(env, "Invalid file type.", 0));
	env->file = path;
}
