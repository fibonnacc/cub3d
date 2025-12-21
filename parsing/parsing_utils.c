/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:47:51 by nafarid           #+#    #+#             */
/*   Updated: 2025/12/07 16:59:26 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	normalize_spaces(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	line_last_visible(const char *s)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != ' ')
			last = i;
		i++;
	}
	return (last);
}

int	line_first_visible(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (!s[i] || s[i] == '\n')
		return (-1);
	return (i);
}

int	is_wall_line(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != '1' && s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
