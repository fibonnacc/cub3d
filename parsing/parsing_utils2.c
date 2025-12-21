/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 09:37:28 by nafarid           #+#    #+#             */
/*   Updated: 2025/12/06 16:19:45 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_linelen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static int	is_void(char **map, int i, int j)
{
	int	len;

	if (i < 0 || j < 0)
		return (1);
	if (!map[i])
		return (1);
	len = ft_linelen(map[i]);
	if (j >= len)
		return (1);
	if (map[i][j] == ' ' || map[i][j] == '\n')
		return (1);
	return (0);
}

int	check_space_is_valid(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || is_player(map[i][j]))
			{
				if (is_void(map, i, j - 1) || is_void(map, i, j + 1)
					|| is_void(map, i - 1, j) || is_void(map, i + 1, j))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
