/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_parser_struct.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 21:46:31 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/22 15:03:18 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_PARSER_STRUCT_H
# define XPM_PARSER_STRUCT_H

typedef struct		s_text
{
	unsigned int	*str;
	int				w;
	int				h;
}					t_text;

typedef struct		s_pixel
{
	int				x;
	int				y;
}					t_pixel;

typedef struct		s_color_p
{
	char			*id;
	int				value;
}					t_color_p;

typedef struct		s_parser
{
	int				i;
	int				j;
	int				fd;
	int				ret;
	int				size;
	t_pixel			info;
	t_color_p		*color;
	char			*path;
	char			*line;
	char			**tabtmp;
	char			*tmp;
	char			*raw;
	t_text			texture;
}					t_parser;

#endif
