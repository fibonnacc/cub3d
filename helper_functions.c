#include "cub3d.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	if (!dst || !src)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void  add_back(t_cub3d **list, t_cub3d *new)
{
  t_cub3d *current;

  if (!list || !new)
    return;
  if (!*list)
  {
    *list = new;
    return;
  }
  current = *list;
  while (current->next)
  {
    current = current->next;
  }
  current->next = new;
}

t_cub3d *new_node(char *content)
{
  t_cub3d *node;
  
  node = malloc(sizeof(t_cub3d));
  if (!node)
    return (NULL);
  node->data = malloc(sizeof(char));
  if (!node->data)
  {
    free(node);
    return (NULL);
  }
  ft_strcpy(node->data, content);
  node->next = NULL;
  return (node);
}

