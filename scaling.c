/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <helfatih@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:45 by helfatih          #+#    #+#             */
/*   Updated: 2025/11/28 10:56:45 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_texture_x(t_var *var, t_intersection *res, t_texture *texture)
{
	if (res->is_vertical)
	{
		var->wall_hit = res->y - floor(res->y);
		var->tex_x = (int)(var->wall_hit * texture->img_width);
	}
	else
	{
		var->wall_hit = res->x - floor(res->x);
		var->tex_x = (int)(var->wall_hit * texture->img_width);
	}
}

void	init_texture_rendering(t_var *var, t_texture *texture)
{
	var->step = (double)texture->img_height / var->wall_strip_height;
}

void	draw_textured_column(t_data *data, t_var *var, int i,
		t_texture *texture)
{
	int	y;
	int	tex_y;
	int	color;
	int	relative_y;

	y = var->draw_start;
	while (y < var->draw_end)
	{
		relative_y = y - var->wall_top_pixel;
		tex_y = (int)(relative_y * var->step);
		if (tex_y < 0 || tex_y >= texture->img_height)
			tex_y = 0;
		else
		{
			color = get_texture_color(texture, var->tex_x, tex_y);
			my_mlx_pixel_put(data, i, y, color);
		}
		y++;
	}
}
