/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:43 by helfatih          #+#    #+#             */
/*   Updated: 2025/12/07 11:03:24 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_intersection	*cast_ray_to_wall(t_data *data, double ray_angle, int color)
{
	double			player_x;
	double			player_y;
	t_intersection	horz;
	t_intersection	vert;
	t_intersection	*closest;

	(void)color;
	player_x = data->player.x;
	player_y = data->player.y;
	horz = get_horizontal_intersection(data, player_x, player_y, ray_angle);
	vert = get_vertical_intersection(data, player_x, player_y, ray_angle);
	closest = ft_malloc(sizeof(t_intersection));
	if (horz.distance < vert.distance)
	{
		*closest = horz;
		closest->is_vertical = 0;
	}
	else
	{
		*closest = vert;
		closest->is_vertical = 1;
	}
	return (closest);
}

t_intersection	*cast_single_ray(t_data *data, t_var *var)
{
	var->ray_angle = var->start_angle;
	return (cast_ray_to_wall(data, var->ray_angle, 0xFFFFFF));
}
