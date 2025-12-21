/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:12:59 by nafarid           #+#    #+#             */
/*   Updated: 2025/12/02 16:46:23 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_gc	*create_node(void *data)
{
	t_gc	*new_node;

	new_node = malloc(sizeof(t_gc));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->next = NULL;
	return (new_node);
}

t_gc	*get_garbage_collecter(void *ptr)
{
	static t_gc	*gc;
	t_gc		*new_gc;

	if (ptr)
	{
		new_gc = create_node(ptr);
		new_gc->next = gc;
		gc = new_gc;
	}
	return (gc);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("Error\nMalloc failled\n");
		free_grabage();
		exit(2);
	}
	get_garbage_collecter(ptr);
	return (ptr);
}

void	free_grabage(void)
{
	t_gc	*gc;
	t_gc	*tmp;

	gc = get_garbage_collecter(NULL);
	while (gc)
	{
		tmp = gc;
		gc = gc->next;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp);
		tmp = NULL;
	}
}
