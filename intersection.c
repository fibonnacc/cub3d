/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <helfatih@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:28 by helfatih          #+#    #+#             */
/*   Updated: 2025/11/28 10:56:28 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_wall(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x);
	map_y = (int)(y);
	if (map_x < 0 || map_x >= data->map_width || map_y < 0
		|| map_y >= data->map_height)
		return (true);
	return (data->map->map[map_y][map_x] == '1');
}

t_intersection	get_horizontal_intersection(t_data *data, double player_x,
		double player_y, double angle)
{
	t_elem	elem;

	init_element(&elem, player_y, player_x, angle);
	horz_intersection(&elem);
	while (elem.next_x >= 0 && elem.next_x <= data->map_width
		&& elem.next_y >= 0 && elem.next_y < data->map_height)
	{
		elem.check_y = elem.next_y;
		if (facing_up(angle))
			elem.check_y -= 0.001;
		if (horz_hit_wall(data, &elem))
			break ;
		elem.next_x += elem.xstep;
		elem.next_y += elem.ystep;
	}
	return (elem.res);
}

t_intersection	get_vertical_intersection(t_data *data, double player_x,
		double player_y, double angle)
{
	t_elem	elem;

	init_element(&elem, player_y, player_x, angle);
	vert_intersection(&elem);
	while (elem.next_x >= 0 && elem.next_x <= data->map_width
		&& elem.next_y >= 0 && elem.next_y <= data->map_height)
	{
		elem.check_x = elem.next_x;
		if (facing_left(elem.angle))
			elem.check_x -= 0.001;
		if (vert_hit_wall(data, &elem))
			break ;
		elem.next_x += elem.xstep;
		elem.next_y += elem.ystep;
	}
	return (elem.res);
}
