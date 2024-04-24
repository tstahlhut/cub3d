/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:17:05 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/24 15:35:43 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	check_only_valid_token(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	if (line[i] == 'S' && line[i + 1] == 'O')
		return (0);
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (0);
	if (line[i] == 'W' && line[i + 1] == 'E')
		return (0);
	if (line[i] == 'E' && line[i + 1] == 'A')
		return (0);
	if (line[i] == '1' || line[i] == '2')
		return (0);
	if (line[i] == 'F' || line[i] == 'C')
		return (0);
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	return (-1);
}

void	init_movement(t_cub *cub)
{
	cub->m_flag.move_down = 0;
	cub->m_flag.move_left = 0;
	cub->m_flag.move_right = 0;
	cub->m_flag.move_up = 0;
	cub->m_flag.look_left = 0;
	cub->m_flag.look_right = 0;
	cub->m_flag.map_flag = 0;
}

/* init_cub: The variables of struct cub are initialized.
	All pointers and flags are set to zero.*/

void	init_cub(t_cub *cub)
{
	init_movement(cub);
	cub->exit_flag = 0;
	cub->exit_found = 0;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->img = NULL;
	cub->img_exit.img = NULL;
}

/* Variables shortly explained:
	1. dir[2]; direction player is facing: dir[0] = dir_x, dir[1] = dir_y
		We get pos and dir from map (N, E, W, S).
	2. camplane[2]; camera plane of player, needs to be perpendicular to dir
		The FOV (Field of View) is determined by ratio between length of 
			direction and camera plane; camplane is set to [0, 0.66] 
			which creates perfect FOV of 66°*/

void	init_dir(t_cub *cub, char c)
{
	if (c == 'N' || c == 'S')
	{
		cub->dir[1] = 1;
		if (c == 'N')
			cub->dir[1] = -1;
		cub->dir[0] = 0;
		cub->camplane[1] = 0;
		cub->camplane[0] = -0.66 * cub->dir[1];
	}
	if (c == 'E' || c == 'W')
	{
		cub->dir[1] = 0;
		cub->dir[0] = 1;
		if (c == 'W')
			cub->dir[0] = -1;
		cub->camplane[1] = -0.66 * cub->dir[0];
		cub->camplane[0] = 0;
	}
}

void	init_img(t_cub *cub, int width, int height)
{
	t_img	*img;

	cub->img = malloc(sizeof(t_img));
	if (!cub->img)
		error_exit(cub, "malloc image failed", NULL);
	img = cub->img;
	img->img = mlx_new_image(cub->mlx, width, height);
	if (!img->img)
		error_exit(cub, "image could not be initialized", NULL);
	img->addr = mlx_get_data_addr \
	(img->img, &img->bpp, &img->line_length, &img->endian);
	if (!img->addr)
		error_exit(cub, "image information could not be retrieved", NULL);
}
