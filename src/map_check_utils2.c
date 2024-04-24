/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:08 by leschenb          #+#    #+#             */
/*   Updated: 2024/04/24 11:32:28 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	check_first_row(t_cub *cube)
{
	int	x;

	x = 0;
	while (x < cube->map->max_line_len && cube->map->layout[0][x] != '\0')
	{
		if ((!ft_isspace(cube->map->layout[0][x]))
			&& (cube->map->layout[0][x] != '1'
				&& cube->map->layout[0][x] != '2'))
			return (-1);
		x++;
	}
	return (0);
}

int	validate_cube(t_cub *cube)
{
	if (cube == NULL || cube->map == NULL || cube->map->layout == NULL
		|| cube->map->nlines < 3)
		return (-1);
	if (check_first_row(cube) == -1)
		return (-1);
	return (0);
}

int	process_character(t_cub *cube, int x, int y, int *playercount)
{
	char	c;

	c = cube->map->layout[y][x];
	if (c != '0' && c != '1' && c != '2' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != ' ')
	{
		printf("invalid char on map\n");
		return (-1);
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*playercount)++;
		cube->pos[0] = x + 0.5;
		cube->pos[1] = y + 0.5;
		set_angle(cube, c);
		init_dir(cube, c);
		cube->map->layout[y][x] = '0';
	}
	if (c == '2')
	{
		cube->exit_flag = 1;
		cube->exit_pos[0] = x;
		cube->exit_pos[1] = y;
	}
	return (0);
}

int	check_player_count(int playercount)
{
	if (playercount != 1)
	{
		printf("TO MANY PLAYERS ON MAP");
		return (-1);
	}
	return (0);
}

int	check_all_rows(t_cub *cube)
{
	char	c;
	int		x;
	int		y;
	int		playercount;

	x = 0;
	y = 0;
	playercount = 0;
	if (validate_cube(cube) == -1)
		return (-1);
	y++;
	while (y < cube->map->nlines - 1)
	{
		while (cube->map->layout[y][x] != '\0')
		{
			c = cube->map->layout[y][x];
			process_character(cube, x, y, &playercount);
			x++;
		}
		x = 0;
		y++;
	}
	return (check_player_count(playercount));
}
