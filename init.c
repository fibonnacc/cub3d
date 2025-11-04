#include "cub3d.h"

void  my_mlx_pixel_put(t_data *data, int i, int j, int color)
{
  char *dst;

  if (i < 0 || i >= WIN_HEIGHT || j < 0 || j >= WIN_WIDTH )
    return ;
  dst = data->addr + (i * data->line_length + j * (data->bits_per_pixels / 8));
  *(unsigned int*)dst =  color;
}


void draw_square(t_data *data, int x, int y, int size, int color)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            my_mlx_pixel_put(data, x + j, y + i, color);
        }
    }
}

void  draw_map(t_data *data)
{
  int i;
  int j;

  i = 0;
  while (i < WIN_HEIGHT)
  {
    j = 0;
    while (j < WIN_WIDTH)
    {
      my_mlx_pixel_put(data, i, j, 0x000000);
      j++;
    }
    i++;
  }

  i = 0;
  while (i < data->map_height)
  {
    j = 0;
    while (j < data->map_width)
    {
      int x = i * data->tile_size;
      int y = j * data->tile_size;

      if (data->maps[i][j] == '1')
        draw_square(data, x, y, data->tile_size, 0xFF0000);
      else {
        draw_square(data, x, y, data->tile_size, 0x00FF00);
      }
      for (int k = 0; k < data->tile_size; k++)
      {
        my_mlx_pixel_put(data, x + k, y, 0xFFFF00);
        my_mlx_pixel_put(data, x, y + k, 0xFFFF00);
      }
      j++;
    }
    i++;
  }
  draw_player(data);
}

char **creat_map()
{
  int i;
  char **maps = malloc(sizeof(char *) * 10);
  if (!maps)
    return (NULL);
  char temp_maps[10][13] = {
    "111111111111",
    "100000000001",
    "100000000001",
    "100011100001",
    "100000100001",
    "100001000001",
    "100000000001",
    "100000000001",
    "100000001111",
    "111111111111"
  };

  i = 0;
  while (i < 10)
  {
    maps[i] = malloc(14);
    if (!maps[i])
    {
      while (--i >= 0)
      {
        free(maps[i]);
      }
      free(maps);
      return NULL;
    }
    ft_strcpy(maps[i], temp_maps[i]);
    i++;
  }
  return (maps);
}

int check_collision(t_data *data, double new_x, double new_y)
{
    int map_x = (int)new_x;
    int map_y = (int)new_y;
    
    // Check boundaries
    if (map_x < 0 || map_x >= data->map_width || 
        map_y < 0 || map_y >= data->map_height)
        return (1); // Collision with boundary
    
    // Check if position is a wall
    if (data->maps[map_y][map_x] == '1')
        return (1); // Collision with wall
    
    return (0); // No collision
}

int key_press(int keycode, t_data *data)
{
    double move_speed = 0.5; // Adjust speed as needed
    double new_x = data->player.x;
    double new_y = data->player.y;
    
    // Arrow keys or WASD
    if (keycode == 65363 || keycode == 'd') // Right arrow or D
        new_x += move_speed;
    else if (keycode == 65361 || keycode == 'a') // Left arrow or A
        new_x -= move_speed;
    else if (keycode == 65362 || keycode == 'w') // Up arrow or W
        new_y -= move_speed;
    else if (keycode == 65364 || keycode == 's') // Down arrow or S
        new_y += move_speed;
    else if (keycode == 65307) // ESC key
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    
    // Check collision before moving
    if (!check_collision(data, new_x, new_y))
    {
        data->player.x = new_x;
        data->player.y = new_y;
        render_frame(data); // Redraw the frame
    }
    
    return (0);
}

void draw_player(t_data *data)
{
    int player_screen_x = (int)(data->player.x * data->tile_size);
    int player_screen_y = (int)(data->player.y * data->tile_size);
    int player_size = data->tile_size / 3; // Player is 1/3 of a tile
    
    // Draw player as a colored square (you can make it a circle if you want)
    for (int i = -player_size/2; i < player_size/2; i++)
    {
        for (int j = -player_size/2; j < player_size/2; j++)
        {
            my_mlx_pixel_put(data, player_screen_x + j, player_screen_y + i, 0xFF0000); // Red color
        }
    }
}


void init_mlx(t_data *data)
{
  data->mlx =  mlx_init();
  data->win = mlx_new_window(data->mlx, 600, 500, "Hicham el fatihi");
  data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
  data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixels, &data->line_length, &data->endian);
  printf("the value of line_length : %d\n", data->line_length);
  printf("the value of the bits_per_pixels : %d\n", data->bits_per_pixels);
  printf("the value of the endian : %d\n", data->endian);

  int tile_width = WIN_WIDTH / data->map_width;
  int tile_height = WIN_HEIGHT / data->map_height;
  data->tile_size = (tile_width < tile_height) ? tile_width : tile_height;
}
