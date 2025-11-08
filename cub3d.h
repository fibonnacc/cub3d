#ifndef CUB3D_H
#define CUB3D_H

#define TILE_SIZE 32
#define WIN_WIDTH 800
#define WIN_HEIGHT 800
#define ROT_SPEED 0.3  // Rotation speed in radians
#define MOVE_SPEED 0.2  // Movement speed
#define FOV (M_PI / 3)  // 60 degrees field of view
#define NUM_RAYS 80

#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "./get_next_line/get_next_line.h"
#include "./minilibx-linux/mlx.h"

typedef struct s_cub3d
{
  char *data;
  struct s_cub3d *next;
} t_cub3d;


typedef struct s_joueur
{
  double  x;
  double  y;
  double angle;

} t_joueur;

typedef struct s_data
{
  void *mlx;
  void *img;
  void  *win;
  char  *addr;
  int   line_length;
  int   bits_per_pixels;
  int   endian;
  t_joueur  player;
  char  **maps;
  int   map_width;
  int   map_height;
  int   tile_size;
} t_data;



void init_mlx(t_data *data);

char **creat_map();
void  render_frame(t_data *data);
void  my_mlx_pixel_put(t_data *data, int x, int y, int color);
// void  my_mlx_put_pixel(t_data *data, int i, int j, int color);
void draw_player(t_data *data);
int check_collision(t_data *data, double new_x, double new_y);

int key_press(int keycode, t_data *data);

void draw_fov_cone(t_data *data);
void draw_fov(t_data *data);
void cast_ray_to_wall(t_data *data, double ray_angle, int color);
void draw_fov_with_walls(t_data *data);

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color);
void draw_direction_line(t_data *data);
void  draw_map(t_data *data);
char	*ft_strcpy(char *dst, const char *src);
void  add_back(t_cub3d **list, t_cub3d *new);
t_cub3d *new_node(char *content);

#endif // !CUB3D_H
