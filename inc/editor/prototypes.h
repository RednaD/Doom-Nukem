/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:52:21 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/22 16:04:04 by stsavida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

void		ft_exit(t_env *env, int exitcode);

void		ft_init_env(t_env *env);
void		ft_init_window(t_env *env);
void		ft_init_hooks(t_env *env);
void		ft_init_text(t_env *env);
void		ft_init_texture(t_env *env, t_texture **texture, char *path,
	int id);
void		ft_draw_grid(t_env *env);

void		ft_putpixel(t_image image, int x, int y, int color);
void		ft_copypixel(t_image image_from, t_coord coord_from,
	t_image image_to, t_coord coord_to);
void		ft_display_current_texture(t_env *env);
void		ft_copy_texture(t_texture *texture, t_image *image,
	int desired_width, int desired_height);

void		ft_load_textures(t_env *env);
void		ft_load_texture(t_env *env, int id, char *path, int mode);
void		ft_put_texture(t_env *env, int x, int y, t_texture *texture);
void		ft_push_texture(t_env *env, t_texture *texture, int mode);

void		ft_export(t_env *env, char *path);
void		ft_export_header(t_env *env, int fd);
void		ft_import(t_env *env, char *path);
void		ft_check_file(t_env *env, char *path);
void		ft_parse_file_header(t_env *env, char *line);
void		ft_generate_points_from_line(t_env *env, char *line, int y);
t_texture	*ft_find_in_texture(int id, t_texture *find_in);
t_texture	*ft_find_texture(t_env *env, int id);

int			ft_onmouseclick(int button, int x, int y, t_env *env);
int			ft_checkbox_onmouseclick(int button, int x, int y, t_env *env);
int			ft_onkeypress(int keycode, t_env *env);
void		ft_swap_mode(t_env *env, int mode);
int			ft_onkeypressl(int keycode, t_env *env);

void		ft_void_point(t_env *env, t_point *point, int pos_x, int pos_y);

void		ft_throw_error(t_env *env, char *msg);
void		*ft_malloc_or_throw(t_env *env, int size);
void		ft_free_textures(t_env *env, t_texture *texture);
void		ft_free_texture(t_env *env, t_texture *texture);
void		ft_free_image(t_env *env, t_image *image);

void		ft_resize_up(t_texture *texture, t_image *image,
	int desired_width, int desired_height);
void		ft_resize_down(t_texture *texture, t_image *image,
	int desired_width, int desired_height);

void		ft_display_life(t_env *env);
void		ft_display_sky_mode_checkbox(t_env *env, t_image **display,
	int checked, t_coord display_coord);

void		ft_alloc_image(t_env *env, t_image **image, int width, int height);

int			ft_quit(t_env *env);

void		exit_doom(t_env *env, char *err);

void		ft_convert_int_to_string(t_text xmp, t_image *image);

#endif
