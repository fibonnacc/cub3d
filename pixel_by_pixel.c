/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_by_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <helfatih@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:09:28 by helfatih          #+#    #+#             */
/*   Updated: 2025/11/28 22:09:30 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (y < 0 || y >= WIN_HEIGHT || x < 0 || x >= WIN_WIDTH)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixels
				/ 8));
	*(unsigned int *)dst = color;
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			if (i < WIN_HEIGHT / 2)
				my_mlx_pixel_put(data, j, i, data->map->celling);
			else
				my_mlx_pixel_put(data, j, i, data->map->floor);
			j++;
		}
		i++;
	}
	draw_player(data);
}
