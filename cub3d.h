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

void  add_back(t_cub3d **list, t_cub3d *new);
t_cub3d *new_node(char *content);

#endif // !CUB3D_H
