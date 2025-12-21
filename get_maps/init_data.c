/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:55:18 by nafarid           #+#    #+#             */
/*   Updated: 2025/12/07 16:38:42 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_char(char *ptr, char c, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (ptr[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	open_fd(t_data *data, char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		free_grabage();
		exit(1);
	}
	data->map->fd = fd;
}

void	init_data(t_data *data)
{
	data->map = ft_malloc(sizeof(t_map));
	data->map->north = ft_malloc(sizeof(t_texture));
	data->map->south = ft_malloc(sizeof(t_texture));
	data->map->west = ft_malloc(sizeof(t_texture));
	data->map->east = ft_malloc(sizeof(t_texture));
	data->map->floor = 0;
	data->map->celling = 0;
	data->map->map = NULL;
	data->map->fd = -1;
	data->player.x = 0.0;
	data->player.y = 0.0;
	data->map->east->img = NULL;
	data->win = NULL;
	data->img = NULL;
}

void	exit_and_error(t_data *data, int flag)
{
	if (flag == 1)
	{
		printf("Error\nInvalid configuration\n");
		close(data->map->fd);
		free_grabage();
		exit(1);
	}
	if (flag == 2)
	{
		printf("Error\nIdentifier after map\n");
		close(data->map->fd);
		free_grabage();
		exit(1);
	}
}

int	skip_whitespace(char **str)
{
	if (!str || !*str)
		return (1);
	while (**str && (**str == ' ' || **str == '\t'))
		(*str)++;
	return (0);
}
