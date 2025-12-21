/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:37 by helfatih          #+#    #+#             */
/*   Updated: 2025/11/29 12:04:12 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	load_one_texture(t_data *data, t_texture *tex)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, tex->file, &tex->img_width,
			&tex->img_height);
	if (!tex->img)
		return (false);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		return (false);
	return (true);
}

bool	upload_textures(t_data *data)
{
	if (!load_one_texture(data, data->map->north))
		return (false);
	if (!load_one_texture(data, data->map->south))
		return (false);
	if (!load_one_texture(data, data->map->west))
		return (false);
	if (!load_one_texture(data, data->map->east))
		return (false);
	return (true);
}
