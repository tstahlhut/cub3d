/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:35:22 by leschenb          #+#    #+#             */
/*   Updated: 2024/04/24 16:02:26 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/* Wenn man sich bei der map eingabe vertippt, segfaulted die Funktion*/

void	set_angle(t_cub *cube, char c)
{
	cube->map->initial_dir = c;
	if (c == 'N')
	{
		cube->dir[0] = 0;
		cube->dir[1] = -1;
	}
	if (c == 'E')
	{
		cube->dir[0] = 1;
		cube->dir[1] = 0;
	}
	if (c == 'S')
	{
		cube->dir[0] = 0;
		cube->dir[1] = 1;
	}
	if (c == 'W')
	{
		cube->dir[0] = -1;
		cube->dir[1] = 0;
	}
}

int	flood_fill_check(char **layout, int x, int y, t_cub *cub)
{
	int	xmax;
	int	ymax;

	xmax = cub->map->max_line_len;
	ymax = cub->map->nlines;
	if (x < 0 || y < 0 || x >= xmax || y >= ymax)
		return (-1);
	if (layout[y][x] == 'x' || layout[y][x] == '1' || layout[y][x] == '2')
		return (0);
	layout[y][x] = 'x';
	if (flood_fill_check(layout, x + 1, y, cub) == -1
		|| flood_fill_check(layout, x - 1, y, cub) == -1
		|| flood_fill_check(layout, x, y + 1, cub) == -1
		|| flood_fill_check(layout, x, y - 1, cub) == -1)
	{
		return (-1);
	}
	return (0);
}

int	ft_flood_fill(t_cub *cube)
{
	char	**layout_copy;
	int		i;

	i = 0;
	layout_copy = malloc(sizeof(char *) * cube->map->nlines);
	while (i < cube->map->nlines)
	{
		layout_copy[i] = malloc(sizeof(char) * (cube->map->max_line_len + 1));
		ft_strcpy(layout_copy[i], cube->map->layout[i]);
		i++;
	}
	if (flood_fill_check(layout_copy, cube->pos[0] - 0.5, cube->pos[1] - 0.5,
			cube) == -1)
		return (-1);
	i = 0;
	while (i < cube->map->nlines)
	{
		free(layout_copy[i]);
		i++;
	}
	free(layout_copy);
	return (0);
}

int	map_check(t_cub *cube)
{
	if (cube->map->map_valid_flag == -1)
		return (-1);
	checkcolor(cube);
	if (cube->map->map_valid_flag == -1)
		error_exit(cube, "map color invalid", NULL);
	if (check_textures(cube->map->no) == -1)
		error_exit(cube, "texture not found", cube->map->no);
	if (check_textures(cube->map->so) == -1)
		error_exit(cube, "texture not found", cube->map->so);
	if (check_textures(cube->map->we) == -1)
		error_exit(cube, "texture not found", cube->map->we);
	if (check_textures(cube->map->ea) == -1)
		error_exit(cube, "texture not found", cube->map->ea);
	if (check_all_rows(cube) == -1)
		cube->map->map_valid_flag = -1;
	if (ft_flood_fill(cube) == -1)
		cube->map->map_valid_flag = -1;
	if (cube->map->map_valid_flag == -1)
		return (printf("map invalid\n"), -1);
	return (0);
}
