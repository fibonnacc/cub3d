
#include "cub3d.h"
#include <threads.h>

void print_list(t_cub3d *cur)
{
  t_cub3d *current = cur;
  while (current)
  {
    printf("%s", current->data);
    current = current->next;
  }
}

void clear_list(t_cub3d **list)
{
  t_cub3d *current;
  t_cub3d *next;

  if (!list || !*list)
    return;
  current = *list;
  while (current)
  {
    next = current->next;
    free(current->data);
    free(current);
    current = next;
  }
  current = NULL;
}

void  make_copy_map(int ac, char *av[])
{
  char *line;
  int fd;
  char *maps = av[1];
  t_cub3d *head = NULL;

  if (ac != 2)
  {
    printf("Error\n");
    return;
  }

  fd = open(maps, O_RDWR);
  if (fd < 0)
  {
    printf("Error\n");
    return ;
  }

  while ((line = get_next_line(fd)))
  {
    add_back(&head, new_node(line));
    free(line);
  }
  clear_list(&head);
  close (fd);
}

void free_all(t_data *data)
{
  int i = 0;
  while (i < data->map_height)
  {
    free(data->maps[i]);
    i++;
  }
  free(data->maps);
  free(data);
}

int main(int ac, char *av[])
{
  (void)av;
  (void)ac;
  t_data *data = malloc(sizeof(t_data));;
  if (!data)
    return (1);

  data->maps = creat_map();

  data->map_width = 12;
  data->map_height = 10;

  data->player.x = 1.0;
  data->player.y = 2.0;

  init_mlx(data);

  render_frame(data);
  mlx_key_hook(data->win, key_press, data);

  // make_copy_map(ac, av);
  mlx_loop(data->mlx);
  free_all(data);
}
