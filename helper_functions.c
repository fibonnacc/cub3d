/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <helfatih@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:08 by helfatih          #+#    #+#             */
/*   Updated: 2025/11/28 21:01:47 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(t_data *data)
{
	draw_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	free_resource_of_map(t_map **map, t_data *data)
{
	*map = data->map;
	if ((*map)->north && (*map)->north->img)
		mlx_destroy_image(data->mlx, (*map)->north->img);
	if ((*map)->south && (*map)->south->img)
		mlx_destroy_image(data->mlx, (*map)->south->img);
	if ((*map)->west && (*map)->west->img)
		mlx_destroy_image(data->mlx, (*map)->west->img);
	if ((*map)->east && (*map)->east->img)
		mlx_destroy_image(data->mlx, (*map)->east->img);
}

void	cleanup(t_data *data)
{
	t_map	*map;

	if (!data)
		return ;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->map)
	{
		free_resource_of_map(&map, data);
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free_grabage();
}
