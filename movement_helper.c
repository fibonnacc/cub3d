/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <helfatih@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:03:54 by helfatih          #+#    #+#             */
/*   Updated: 2025/11/28 22:03:54 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_movement_key(int keycode)
{
	return (keycode == 'w' || keycode == 65362 || keycode == 's'
		|| keycode == 65364 || keycode == 'a' || keycode == 'd');
}

int	is_rotation_key(int keycode)
{
	return (keycode == 65363 || keycode == 65361);
}
