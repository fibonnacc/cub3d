/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rayes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:55:58 by helfatih          #+#    #+#             */
/*   Updated: 2025/12/07 11:03:41 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_fov_variables(t_data *data, t_var *var)
{
	var->start_angle = data->player.angle - (FOV / 2);
	var->angle_step = FOV / NUM_RAYS;
	var->distance_proj_plane = 1600;
}

void	calculate_wall_projection(t_data *data, t_var *var, t_intersection *res)
{
	var->perp_distance = res->distance * cos(var->ray_angle
			- data->player.angle);
	var->wall_strip_height = var->distance_proj_plane / var->perp_distance;
	var->wall_top_pixel = (WIN_HEIGHT / 2) - (var->wall_strip_height / 2);
	var->wall_bottom_pixel = (WIN_HEIGHT / 2) + (var->wall_strip_height / 2);
}

void	calculate_draw_bounds(t_var *var)
{
	var->draw_start = var->wall_top_pixel;
	if (var->draw_start < 0)
		var->draw_start = 0;
	var->draw_end = var->wall_bottom_pixel;
	if (var->draw_end > WIN_HEIGHT)
		var->draw_end = WIN_HEIGHT;
}

void	process_ray_column(t_data *data, t_var *var, int i)
{
	t_intersection	*res;
	t_texture		*texture;

	res = cast_single_ray(data, var);
	calculate_wall_projection(data, var, res);
	calculate_draw_bounds(var);
	texture = get_wall_texture(data, res, var->ray_angle);
	calculate_texture_x(var, res, texture);
	init_texture_rendering(var, texture);
	draw_textured_column(data, var, i, texture);
}

void	draw_fov_with_walls(t_data *data)
{
	t_var	var;
	int		i;

	init_fov_variables(data, &var);
	i = 0;
	while (i < NUM_RAYS)
	{
		process_ray_column(data, &var, i);
		var.start_angle += var.angle_step;
		i++;
	}
}
