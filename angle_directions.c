/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:40:32 by helfatih          #+#    #+#             */
/*   Updated: 2025/12/02 17:42:28 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	facing_down(double angle)
{
	return (sin(angle) > 0);
}

bool	facing_up(double angle)
{
	return (sin(angle) < 0);
}

bool	facing_left(double angle)
{
	return (cos(angle) < 0);
}

bool	facing_right(double angle)
{
	return (cos(angle) > 0);
}
