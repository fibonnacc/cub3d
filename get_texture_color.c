/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:00 by helfatih          #+#    #+#             */
/*   Updated: 2025/12/03 12:12:01 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_texture_color(t_texture *tex, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0 || tex_x >= tex->img_width || tex_y < 0
		|| tex_y >= tex->img_height)
		return (0x000000);
	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

t_texture	*get_wall_texture(t_data *data, t_intersection *res,
		double ray_angle)
{
	if (res->is_vertical)
	{
		if (cos(ray_angle) < 0)
			return (data->map->west);
		else
			return (data->map->east);
	}
	else
	{
		if (sin(ray_angle) > 0)
			return (data->map->south);
		else
			return (data->map->north);
	}
}
