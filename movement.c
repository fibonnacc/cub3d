/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <helfatih@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:06:54 by helfatih          #+#    #+#             */
/*   Updated: 2025/11/28 21:06:54 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_key_rotation(t_data *data, int keycode)
{
	if (keycode == 65363)
	{
		data->player.angle += ROT_SPEED;
	}
	else if (keycode == 65361)
	{
		data->player.angle -= ROT_SPEED;
	}
}

void	for_and_back(int keycode, t_data *data, double *new_y, double *new_x)
{
	double	move_speed;

	move_speed = MOVE_SPEED;
	if (keycode == 'w' || keycode == 65362)
	{
		*new_x += cos(data->player.angle) * move_speed;
		*new_y += sin(data->player.angle) * move_speed;
	}
	else if (keycode == 's' || keycode == 65364)
	{
		*new_x -= cos(data->player.angle) * move_speed;
		*new_y -= sin(data->player.angle) * move_speed;
	}
}

void	left_and_right(int keycode, t_data *data, double *new_y, double *new_x)
{
	double	move_speed;

	move_speed = MOVE_SPEED;
	if (keycode == 'a')
	{
		*new_x += cos(data->player.angle - M_PI / 2) * move_speed;
		*new_y += sin(data->player.angle - M_PI / 2) * move_speed;
	}
	else if (keycode == 'd')
	{
		*new_x += cos(data->player.angle + M_PI / 2) * move_speed;
		*new_y += sin(data->player.angle + M_PI / 2) * move_speed;
	}
}

void	process_movement(int keycode, double *new_x, double *new_y,
		t_data *data)
{
	if (keycode == 'w' || keycode == 's')
		for_and_back(keycode, data, new_y, new_x);
	else if (keycode == 'a' || keycode == 'd')
		left_and_right(keycode, data, new_y, new_x);
}

int	key_press(int keycode, t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x;
	new_y = data->player.y;
	if (keycode == 65307)
	{
		cleanup(data);
		exit(0);
	}
	if (is_movement_key(keycode))
		process_movement(keycode, &new_x, &new_y, data);
	else if (is_rotation_key(keycode))
		handle_key_rotation(data, keycode);
	if (is_movement_key(keycode) && !check_collision_with_radius(data, new_x,
			new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
	render_frame(data);
	return (0);
}
