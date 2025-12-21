/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <helfatih@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:00:56 by helfatih          #+#    #+#             */
/*   Updated: 2025/11/28 18:00:56 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_element(t_elem *elem, double player_y, double player_x,
		double angle)
{
	elem->res.x = 0;
	elem->res.y = 0;
	elem->res.distance = 1e30;
	elem->res.found = false;
	elem->res.is_vertical = false;
	elem->res.texture_x = 0.0;
	elem->angle = angle;
	elem->player_y = player_y;
	elem->player_x = player_x;
}

void	vert_intersection(t_elem *elem)
{
	elem->xintercept = floor(elem->player_x);
	if (facing_right(elem->angle))
		elem->xintercept += 1;
	elem->yintercept = elem->player_y + tan(elem->angle) * (elem->xintercept
			- elem->player_x);
	elem->xstep = 1;
	if (facing_left(elem->angle))
		elem->xstep *= -1;
	elem->ystep = tan(elem->angle) * elem->xstep;
	if ((facing_up(elem->angle) && elem->ystep > 0) || (facing_down(elem->angle)
			&& elem->ystep < 0))
		elem->ystep *= -1;
	elem->next_y = elem->yintercept;
	elem->next_x = elem->xintercept;
}

bool	vert_hit_wall(t_data *data, t_elem *elem)
{
	if (check_wall(data, elem->check_x, elem->next_y))
	{
		elem->res.x = elem->next_x;
		elem->res.y = elem->next_y;
		elem->res.distance = sqrt(pow(elem->next_x - elem->player_x, 2)
				+ pow(elem->next_y - elem->player_y, 2));
		elem->res.found = true;
		return (true);
	}
	return (false);
}

void	horz_intersection(t_elem *elem)
{
	elem->yintercept = floor(elem->player_y);
	if (facing_down(elem->angle))
		elem->yintercept += 1;
	elem->xintercept = elem->player_x + (elem->yintercept - elem->player_y)
		/ tan(elem->angle);
	elem->ystep = 1;
	if ((facing_up(elem->angle) && elem->ystep > 0) || (facing_down(elem->angle)
			&& elem->ystep < 0))
		elem->ystep *= -1;
	elem->xstep = 1 / tan(elem->angle);
	if ((facing_left(elem->angle) && elem->xstep > 0)
		|| (facing_right(elem->angle) && elem->xstep < 0))
		elem->xstep *= -1;
	elem->next_x = elem->xintercept;
	elem->next_y = elem->yintercept;
}

bool	horz_hit_wall(t_data *data, t_elem *elem)
{
	if (check_wall(data, elem->next_x, elem->check_y))
	{
		elem->res.x = elem->next_x;
		elem->res.y = elem->next_y;
		elem->res.distance = sqrt(pow(elem->next_x - elem->player_x, 2)
				+ pow(elem->next_y - elem->player_y, 2));
		elem->res.found = true;
		return (true);
	}
	return (false);
}
