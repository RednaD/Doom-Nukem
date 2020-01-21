/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:59:01 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/22 01:32:43 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/editor/doomnukem.h"
#include <unistd.h>

void	ft_export_header(t_env *env, int fd)
{
	char	*val;

	write(fd, "#", 1);
	val = ft_itoa(env->sky_mode);
	write(fd, val, ft_strlen(val));
	free(val);
	write(fd, ";", 1);
	val = ft_itoa(env->life_level);
	write(fd, val, ft_strlen(val));
	free(val);
	write(fd, "\n", 1);
}

void	ft_export(t_env *env, char *path)
{
	int		x;
	int		y;
	char	*val;
	int		fd;

	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
		ft_throw_error(env, "Unable to open file for saving.");
	y = -1;
	ft_export_header(env, fd);
	while (++y < BOX_COUNT)
	{
		x = -1;
		while (++x < BOX_COUNT)
		{
			val = ft_itoa(env->points[y][x].value);
			write(fd, val, ft_strlen(val));
			free(val);
			if (x != BOX_COUNT - 1)
				write(fd, " ", 1);
		}
		if (y != BOX_COUNT - 1)
			write(fd, "\n", 1);
	}
	close(fd);
}

void	ft_import(t_env *env, char *path)
{
	int		state;
	int		y;
	char	*line;
	int		fd;

	y = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_throw_error(env, "Can't open file."));
	while ((state = get_next_line(fd, &line)) > 0)
	{
		if (y == 0 && line[0] != '#')
			ft_throw_error(env, "Missing header in file.");
		if (y == BOX_COUNT + 1)
			ft_throw_error(env, "Invalid file.");
		if (y == 0 && ++y)
			ft_parse_file_header(env, line);
		else
			ft_generate_points_from_line(env, line, y++ - 1);
		free(line);
	}
	if (state == -1)
		ft_throw_error(env, "Unable to load file.");
	close(fd);
}

void	ft_generate_points_from_line(t_env *env, char *line, int y)
{
	t_texture	*texture;
	int			x;
	char		**rm;
	char		**tab;
	int			value;

	x = -1;
	if (!(tab = ft_strsplit(line, ' ')))
		ft_throw_error(env, "Unable to load file.");
	rm = tab;
	while (*tab && ++x >= 0)
	{
		if (x == BOX_COUNT)
			ft_throw_error(env, "Invalid file.");
		value = ft_atoi(*tab);
		if (!env->spawn_placed && value == SPAWN_ID && (env->spawn_placed = 1))
			texture = env->spawn_texture;
		else if (value == END_ID)
			texture = env->end_texture;
		else
			texture = ft_find_texture(env, value);
		ft_put_texture(env, x, y, texture);
		free(*(tab++));
	}
	free(rm);
}

void	ft_parse_file_header(t_env *env, char *line)
{
	char	**params;

	params = ft_strsplit(line, ';');
	if (params[2] != 0 || params[0][0] != '#')
		ft_throw_error(env, "Invalid header on file.");
	env->sky_mode = ft_atoi(params[0] + 1);
	if (env->sky_mode != SKY_MODE_OPEN && env->sky_mode != SKY_MODE_CLOSED)
		env->sky_mode = SKY_MODE_OPEN;
	env->life_level = ft_atoi(params[1]);
	if (env->life_level > 100)
		env->life_level = 100;
	else if (env->life_level < 1)
		env->life_level = 1;
	free(params[0]);
	free(params[1]);
	free(params);
}
