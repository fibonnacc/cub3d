/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:47 by helfatih          #+#    #+#             */
/*   Updated: 2025/12/07 16:16:30 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TILE_SIZE 32
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define ROT_SPEED 0.07
# define MOVE_SPEED 1.1
# define FOV 1.0471975512
# define NUM_RAYS 1920

# include "./get_next_line/get_next_line.h"
# include "./minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gc
{
	void			*data;
	struct s_gc		*next;
}					t_gc;

typedef struct s_texture
{
	char			*file;
	void			*img;
	char			*addr;
	int				bpp;
	int				endian;
	int				line_len;
	int				img_width;
	int				img_height;
}					t_texture;

typedef struct s_var
{
	double			start_angle;
	double			angle_step;
	double			ray_angle;
	double			perp_distance;
	double			projected_wall_height;
	int				wall_strip_height;
	int				draw_start;
	int				draw_end;
	int				wall_top_pixel;
	int				wall_bottom_pixel;
	int				tex_x;
	double			wall_hit;
	double			step;
	double			tex_pos;
	int				tex_y;
	int				color;
	double			distance_proj_plane;
}					t_var;

typedef struct s_map
{
	t_texture		*north;
	t_texture		*south;
	t_texture		*west;
	t_texture		*east;
	int				fd;
	int				celling;
	int				floor;
	int				map_height;
	int				map_lenght;
	char			**map;
}					t_map;

typedef struct s_intersection
{
	double			x;
	double			y;
	double			distance;
	bool			found;
	bool			is_vertical;
	double			texture_x;
}					t_intersection;

typedef struct s_elem
{
	double			angle;
	double			next_x;
	double			next_y;
	double			check_y;
	double			check_x;
	t_intersection	res;
	double			ystep;
	double			xstep;
	double			yintercept;
	double			xintercept;
	double			player_y;
	double			player_x;
}					t_elem;

typedef struct s_joueur
{
	double			x;
	double			y;
	double			angle;
}					t_joueur;

typedef struct s_cub3d
{
	char			*data;
	struct s_cub3d	*next;
}					t_cub3d;

typedef struct s_data
{
	void			*mlx;
	void			*img;
	void			*win;
	char			*addr;
	int				line_length;
	int				bits_per_pixels;
	int				endian;
	int				len;
	t_joueur		player;
	int				map_width;
	int				map_height;
	int				tile_size;
	t_map			*map;
}					t_data;

bool				facing_right(double angle);
bool				facing_left(double angle);
bool				facing_up(double angle);
bool				facing_down(double angle);
void				exit_and_error(t_data *data, int flag);
int					check_collision_with_radius(t_data *data, double x,
						double y);
bool				init_mlx(t_data *data);
void				cleanup(t_data *data);
int					parse_str(char *str);
unsigned int		get_texture_color(t_texture *tex, int tex_x, int tex_y);
t_texture			*get_wall_texture(t_data *data, t_intersection *res,
						double ray_angle);
bool				upload_textures(t_data *data);
void				calculate_texture_x(t_var *var, t_intersection *res,
						t_texture *texture);
void				init_texture_rendering(t_var *var, t_texture *texture);
void				draw_textured_column(t_data *data, t_var *var, int i,
						t_texture *texture);
int					is_wall(t_data *data, double x, double y);
int					is_rotation_key(int keycode);
int					is_movement_key(int keycode);
bool				check_wall(t_data *data, double x, double y);
bool				horz_hit_wall(t_data *data, t_elem *elem);
void				horz_intersection(t_elem *elem);
void				init_element(t_elem *elem, double player_y, double player_x,
						double angle);
bool				vert_hit_wall(t_data *data, t_elem *elem);
void				vert_intersection(t_elem *elem);
t_intersection		*cast_single_ray(t_data *data, t_var *var);
bool				load_one_texture(t_data *data, t_texture *tex);
void				set_direction(t_data *data, int x, int y);
void				init_location(t_data *data);
void				render_frame(t_data *data);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				draw_player(t_data *data);
int					key_press(int keycode, t_data *data);
t_intersection		get_horizontal_intersection(t_data *data, double player_x,
						double player_y, double angle);
t_intersection		get_vertical_intersection(t_data *data, double player_x,
						double player_y, double angle);
t_intersection		*cast_ray_to_wall(t_data *data, double ray_angle,
						int color);
void				draw_fov_with_walls(t_data *data);
void				draw_map(t_data *data);
int					is_player(char c);
int					is_wall_line(const char *s);
int					line_first_visible(const char *s);
int					line_last_visible(const char *s);
void				normalize_spaces(char **map);
int					parsing(t_data *data);
int					scan_player_and_dims(char **map, t_data *data, int *out_h,
						int *out_w);
char				*ft_strndup(char *s, int n);
int					verify_left_right_walls(char **map);
int					verify_top_bottom(char **map);
int					get_map(t_data *data, char **av);
void				init_data(t_data *data);
void				open_fd(t_data *data, char *av);
int					texture_help(t_data *data, char *str);
void				free_grabage(void);
void				*ft_malloc(size_t size);
int					skip_whitespace(char **str);
int					check_attribute(char *str);
int					check_char(char *ptr, char c, int len);
int					loop_map(t_data *data, char *line, int *f,
						int *map_started);
int					fun(t_data *data, char *line, int *f);
int					check_last_line_newline(char **map);
int					get_lines(char **av);
int					check_space_is_valid(char **map);
void				map_setter(t_data *data, ssize_t j, char **map);
void				map_str(t_data *data, int j, char **map);
#endif
