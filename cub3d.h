#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "./get_next_line/get_next_line.h"
#include "./minilibx-linux/mlx.h"

typedef struct s_cub3d
{
  char *data;
  struct s_cub3d *next;
} t_cub3d;

typedef

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
  int   map_widths;
  int   map_height;
} t_data;

void  add_back(t_cub3d **list, t_cub3d *new);
t_cub3d *new_node(char *content);

#endif // !CUB3D_H
