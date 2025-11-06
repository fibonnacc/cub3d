#include "cub3d.h"

void  my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
  char *dst;
  
  int win_width = data->map_width * data->tile_size;
  int win_height = data->map_height * data->tile_size;

  if (y < 0 || y >= win_height || x < 0 || x >= win_width)
    return ;
  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixels / 8));
  *(unsigned int*)dst = color;
}

// void  my_mlx_pixel_put(t_data *data, int i, int j, int color)
// {
//   char *dst;
//
//   if (i < 0 || i >= WIN_HEIGHT || j < 0 || j >= WIN_WIDTH )
//     return ;
//   dst = data->addr + (i * data->line_length + j * (data->bits_per_pixels / 8));
//   *(unsigned int*)dst =  color;
// }


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
        draw_square(data, y, x, data->tile_size, 0xFF0000);
      // else {
      //   draw_square(data, x, y, data->tile_size, 0x00FF00);
      // }

      for (int k = 0; k < data->tile_size; k++)
      {
        my_mlx_pixel_put(data, y + k, x, 0xFFFF00);
        my_mlx_pixel_put(data, y, x + k, 0xFFFF00);
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
  char temp_maps[10][18] = {
    "11111111111111111",
    "10000000000101001",
    "10000000000101001",
    "10000000000101001",
    "10000000000101001",
    "10000000000101001",
    "10000000000101001",
    "10000000000101001",
    "10000000000101001",
    "11111111111111111"
  };

  i = 0;
  while (i < 10)
  {
    maps[i] = malloc(18);
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
    double move_speed = 0.4;
    double new_x = data->player.x;
    double new_y = data->player.y;
    
    // Correct Vim keys: h=left, j=down, k=up, l=right
    if (keycode == 'l' || keycode == 65363) // Right
        new_x += move_speed;
    else if (keycode == 'h' || keycode == 65361) // Left
        new_x -= move_speed;
    else if (keycode == 'k' || keycode == 65362) // Up
        new_y -= move_speed;
    else if (keycode == 'j' || keycode == 65364) // Down
        new_y += move_speed;
    else if (keycode == 65307) // ESC key
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    
    if (!check_collision(data, new_x, new_y))
    {
        data->player.x = new_x;
        data->player.y = new_y;
        render_frame(data);
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
            my_mlx_pixel_put(data, player_screen_x + j, player_screen_y + i, 0xFF0F00); // Red color
        }
    }
}

void init_mlx(t_data *data)
{
  data->mlx = mlx_init();
  
  // Calculate proper tile size and window dimensions
  int tile_width = WIN_WIDTH / data->map_width;
  int tile_height = WIN_HEIGHT / data->map_height;
  data->tile_size = (tile_width < tile_height) ? tile_width : tile_height;
  
  // Calculate actual window size to fit the map perfectly
  int window_width = data->map_width * data->tile_size;
  int window_height = data->map_height * data->tile_size;
  
  data->win = mlx_new_window(data->mlx, window_width, window_height, "Hicham el fatihi");
  data->img = mlx_new_image(data->mlx, window_width, window_height);
  data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixels, &data->line_length, &data->endian);
}

