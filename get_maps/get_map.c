/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:54:44 by nafarid           #+#    #+#             */
/*   Updated: 2025/12/07 11:33:59 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	flag(int *f)
{
	int	i;

	i = 0;
	while (i < 6)
		f[i++] = 0;
}

int	fun(t_data *data, char *str, int *flags)
{
	int	attr;

	attr = check_attribute(str);
	if (attr >= 0)
	{
		if (flags[attr] == 1)
			return (1);
		flags[attr] = 1;
		if (texture_help(data, str) == -1)
			return (1);
		return (2);
	}
	return (0);
}

int	check_flag(int *flag)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (flag[i] != 1)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static int	fill_map(t_data *data, char **map, int f[6])
{
	int		i;
	int		ret;
	int		map_started;
	char	*line;

	i = 0;
	ret = 0;
	map_started = 0;
	line = ft_strdup("");
	while (line)
	{
		line = get_next_line(data->map->fd);
		ret = loop_map(data, line, f, &map_started);
		if (ret == 1)
			break ;
		else if (ret == 2)
		{
			if (i == 0)
				continue ;
		}
		map[i++] = ft_strdup(line);
	}
	close(data->map->fd);
	map[i] = NULL;
	return (map_str(data, i, map), check_flag(f));
}

int	get_map(t_data *data, char **av)
{
	char	**map;
	int		f[6];
	int		lines;

	lines = get_lines(av);
	if (lines == 0)
	{
		printf("Error\nEmpty or invalid file\n");
		close(data->map->fd);
		free_grabage();
		exit(1);
	}
	map = ft_malloc(sizeof(char *) * (lines + 1));
	flag(f);
	return (fill_map(data, map, f));
}
