/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:47:54 by nafarid           #+#    #+#             */
/*   Updated: 2025/12/07 11:16:55 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	verify_top_bottom(char **map)
{
	int	top;
	int	bot;

	top = 0;
	while (map[top] && line_last_visible(map[top]) < 0)
		top++;
	if (!map[top])
		return (1);
	bot = top;
	while (map[bot])
		bot++;
	bot--;
	while (bot > top && line_last_visible(map[bot]) < 0)
		bot--;
	if (!is_wall_line(map[top]) || !is_wall_line(map[bot]))
		return (1);
	return (0);
}

int	verify_left_right_walls(char **map)
{
	int	i;
	int	l;
	int	r;

	i = 0;
	while (map[i])
	{
		l = line_first_visible(map[i]);
		r = line_last_visible(map[i]);
		if (r >= 0)
		{
			if (map[i][l] != '1' || map[i][r] != '1')
				return (1);
		}
		i++;
	}
	return (0);
}

static void	process_line(char *line, t_data *data, int i, int *pc)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != '\n')
	{
		if (is_player(line[j]))
		{
			data->player.x = (double)j + 0.5;
			data->player.y = (double)i + 0.5;
			(*pc)++;
		}
		j++;
	}
}

int	scan_player_and_dims(char **map, t_data *data, int *out_h, int *out_w)
{
	int	i;
	int	pc;
	int	w;

	i = 0;
	pc = 0;
	*out_h = 0;
	*out_w = 0;
	while (map[i])
	{
		process_line(map[i], data, i, &pc);
		w = line_last_visible(map[i]) + 1;
		if (w > *out_w)
			*out_w = w;
		(*out_h)++;
		i++;
	}
	return (pc != 1);
}

char	*ft_strndup(char *s, int n)
{
	unsigned int	i;
	char			*ptr;
	int				j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
		i++;
	ptr = ft_malloc((i - n + 1) * sizeof(char));
	i = n;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i] != '\0' && s[i] != '\n')
	{
		ptr[j++] = s[i];
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}
