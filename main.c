/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:31 by helfatih          #+#    #+#             */
/*   Updated: 2025/12/07 11:06:01 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_location(t_data *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			c = data->map->map[i][j];
			if (is_player(c))
			{
				set_direction(data, i, j);
				break ;
			}
			j++;
		}
		i++;
	}
}

int	validate_args_and_init(t_data **data, int ac)
{
	if (ac != 2)
	{
		printf("Error\ninvalide args!\n");
		return (0);
	}
	*data = ft_malloc(sizeof(t_data));
	return (1);
}

int	load_and_parse_map(t_data *data, char **av)
{
	open_fd(data, av[1]);
	if (get_map(data, av) || parsing(data))
	{
		printf("Error\nInvalid map.\n");
		free_grabage();
		return (0);
	}
	return (1);
}

static int	close_window(t_data *data)
{
	cleanup(data);
	exit(0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!validate_args_and_init(&data, ac))
		return (1);
	init_data(data);
	if (!load_and_parse_map(data, av))
		return (1);
	if (!init_mlx(data))
	{
		printf("Error\nInvalid textures\n");
		cleanup(data);
		return (1);
	}
	render_frame(data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop(data->mlx);
	free_grabage();
	return (0);
}
