/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:41:45 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/06 13:29:46 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_coord
{
	int x;
	int y;
}				t_coord;

typedef	struct	s_mlx
{
	void		*mlx_id;
	void		*window_id;
	int			bpp;
	int			endian;
}				t_mlx;

typedef struct	s_image
{
	void	*id;
	char	*str;
	int		bpp;
	int		endian;
	int		size;
}				t_image;

typedef struct	s_point
{
	t_image	*image;
	int		value;
}				t_point;

typedef struct	s_xmp
{
	t_image	*image;
	int		width;
	int		height;
}				t_xmp;

typedef struct	s_texture
{
	int					id;
	t_xmp				*image;
	struct s_texture	*next;
	struct s_texture	*previous;
}				t_texture;

typedef struct	s_env
{
	t_mlx		mlx;
	t_point		points[BOX_COUNT][BOX_COUNT];
	t_image		grid;
	t_image		*texture_display;
	t_image		*sky_mode_display_1;
	t_image		*sky_mode_display_2;
	t_image		*life_level_display;
	t_xmp		*hud;
	t_texture	*current_texture;
	t_texture	*spawn_texture;
	t_texture	*end_texture;
	t_texture	*wall_texture;
	t_texture	*sprite_texture;
	int			current_mode;
	int			spawn_placed;
	char		*file;
	int			sky_mode;
	int			life_level;
}				t_env;

#endif
