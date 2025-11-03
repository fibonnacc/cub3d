
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

int main(int ac, char *av[])
{
  char *line;
  int fd;
  char *maps = av[1];
  t_cub3d *head = NULL;

  if (ac != 2)
  {
    printf("Error\n");
    return 1;
  }

  fd = open(maps, O_RDWR);
  if (fd < 0)
  {
    printf("Error\n");
    return (1);
  }

  while ((line = get_next_line(fd)))
  {
    add_back(&head, new_node(line));
    free(line);
  }
  print_list(head);
  clear_list(&head);
}
