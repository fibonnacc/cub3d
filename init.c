/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:18 by helfatih          #+#    #+#             */
/*   Updated: 2025/12/02 17:51:59 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_direction(t_data *data, int x, int y)
{
	char	c;

	c = data->map->map[x][y];
	if (c == 'N')
		data->player.angle = 3 * M_PI / 2;
	else if (c == 'S')
		data->player.angle = M_PI / 2;
	else if (c == 'E')
		data->player.angle = 0;
	else if (c == 'W')
	{
		data->player.angle = M_PI;
	}
}

int	is_wall(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= data->map_width || map_y < 0
		|| map_y >= data->map_height)
		return (1);
	return (data->map->map[map_y][map_x] == '1');
}

int	check_collision_with_radius(t_data *data, double x, double y)
{
	double	radius;

	radius = 0.09;
	if (is_wall(data, x + radius, y) || is_wall(data, x - radius, y)
		|| is_wall(data, x, y - radius) || is_wall(data, x, y + radius))
		return (1);
	return (0);
}

void	draw_player(t_data *data)
{
	draw_fov_with_walls(data);
}

bool	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	init_location(data);
	if (!upload_textures(data))
		return (false);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT,
			"CubeVision");
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixels,
			&data->line_length, &data->endian);
	return (true);
}
