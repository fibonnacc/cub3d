/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:55:52 by nafarid           #+#    #+#             */
/*   Updated: 2025/12/06 16:27:01 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	parse_rgb_string(char *str)
{
	int	r;
	int	g;
	int	b;

	if (parse_str(str))
		return (-1);
	r = ft_atoi(str);
	while (*str && *str != ',')
		str++;
	if (*str == ',')
		str++;
	g = ft_atoi(str);
	while (*str && *str != ',')
		str++;
	if (*str == ',')
		str++;
	b = ft_atoi(str);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (-1);
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

int	texture_help(t_data *data, char *str)
{
	if (ft_strncmp(str, "NO ", 3) == 0)
		data->map->north->file = ft_strndup(str, 3);
	else if (ft_strncmp(str, "SO ", 3) == 0)
		data->map->south->file = ft_strndup(str, 3);
	else if (ft_strncmp(str, "WE ", 3) == 0)
		data->map->west->file = ft_strndup(str, 3);
	else if (ft_strncmp(str, "EA ", 3) == 0)
		data->map->east->file = ft_strndup(str, 3);
	else if (ft_strncmp(str, "F ", 2) == 0)
		data->map->floor = parse_rgb_string(str + 2);
	else if (ft_strncmp(str, "C ", 2) == 0)
		data->map->celling = parse_rgb_string(str + 2);
	if (data->map->floor == -1 || data->map->celling == -1)
		return (-1);
	else
		return (1);
	return (0);
}

int	check_attribute(char *str)
{
	char	*attr[7];
	ssize_t	i;

	i = 0;
	attr[0] = "NO ";
	attr[1] = "SO ";
	attr[2] = "WE ";
	attr[3] = "EA ";
	attr[4] = "F ";
	attr[5] = "C ";
	attr[6] = NULL;
	while (attr[i])
	{
		if (ft_strncmp(attr[i], str, ft_strlen(attr[i])) == 0)
			break ;
		i++;
	}
	if (i < 6)
		return (i);
	else
		return (-1);
}

int	loop_map(t_data *data, char *line, int *f, int *map_started)
{
	int	i;

	if (!line)
		return (1);
	if (!line[0] || line[0] == '\n')
		return (2);
	i = fun(data, line, f);
	if (i == 1)
		exit_and_error(data, 1);
	else if (i == 2)
	{
		if (*map_started)
			exit_and_error(data, 2);
		return (2);
	}
	*map_started = 1;
	return (0);
}
