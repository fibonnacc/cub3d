/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:18:31 by nafarid           #+#    #+#             */
/*   Updated: 2025/12/07 11:27:56 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	count_lines_in_fd(int fd)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
	}
	return (count);
}

int	get_lines(char **av)
{
	int	fd;
	int	lines;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nNO such file\n");
		free_grabage();
		exit(1);
	}
	lines = count_lines_in_fd(fd);
	close(fd);
	return (lines);
}

void	map_str(t_data *data, int j, char **map)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	data->map->map = ft_malloc(sizeof(char *) * (j + 1));
	while (map[i])
	{
		if (map[i][0] == '\n' || map[i][0] == '\0')
		{
			printf("Error\nInvalid map\n");
			free_grabage();
			exit(1);
		}
		data->map->map[x++] = ft_strdup(map[i]);
		i++;
	}
	data->map->map[x] = NULL;
}

static int	validate_numbers_and_commas(char *str)
{
	int	comma_count;
	int	digit_count;

	comma_count = 0;
	digit_count = 0;
	while (*str && *str != '\n')
	{
		if (ft_isdigit(*str))
			digit_count++;
		else if (*str == ',')
		{
			if (digit_count == 0)
				return (1);
			comma_count++;
			digit_count = 0;
		}
		else
			return (1);
		str++;
	}
	if (digit_count == 0 || comma_count != 2)
		return (1);
	return (0);
}

int	parse_str(char *str)
{
	if (!str || !*str)
		return (1);
	if (skip_whitespace(&str))
		return (1);
	return (validate_numbers_and_commas(str));
}
