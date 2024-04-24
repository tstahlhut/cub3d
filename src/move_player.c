/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:59 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/24 13:37:05 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	rotate_direction(t_cub *cub, double Dangle)
{
	double	angleinradians;
	double	newdirx;
	double	newdiry;
	double	oldcamplanex;

	angleinradians = Dangle * M_PI / 180;
	newdirx = cub->dir[0] * cos(angleinradians) - \
	cub->dir[1] * sin(angleinradians);
	newdiry = cub->dir[0] * sin(angleinradians) + \
	cub->dir[1] * cos(angleinradians);
	cub->dir[0] = newdirx;
	cub->dir[1] = newdiry;
	oldcamplanex = cub->camplane[0];
	cub->camplane[0] = cub->camplane[0] * cos(angleinradians) - \
	cub->camplane[1] * sin(angleinradians);
	cub->camplane[1] = oldcamplanex * sin(angleinradians) + \
	cub->camplane[1] * cos(angleinradians);
}

void	look_right(t_cub *cub)
{
	if (cub->map->initial_dir == 'N' || cub->map->initial_dir == 'S' )
		rotate_direction(cub, 1.5);
	else
		rotate_direction(cub, -1.5);
}

void	look_left(t_cub *cub)
{
	if (cub->map->initial_dir == 'N' || cub->map->initial_dir == 'S' )
		rotate_direction(cub, -1.5);
	else
		rotate_direction(cub, 1.5);
}

void	move_left(t_cub *cub)
{
	double	perp_dir[2];
	double	new_x;
	double	new_y;

	if (cub->map->initial_dir == 'W' || cub->map->initial_dir == 'E')
	{
		perp_dir[0] = -cub->dir[1];
		perp_dir[1] = cub->dir[0];
	}
	else
	{
		perp_dir[0] = cub->dir[1];
		perp_dir[1] = -cub->dir[0];
	}
	new_x = cub->pos[0] + 0.01 * perp_dir[0];
	new_y = cub->pos[1] + 0.01 * perp_dir[1];
	if (cub->map->layout[(int)new_y][(int)new_x] != '1' && \
	cub->map->layout[(int)new_y][(int)new_x] != '2')
	{
		cub->pos[0] = new_x;
		cub->pos[1] = new_y;
	}
}

void	move_right(t_cub *cub)
{
	double	perp_dir[2];
	double	new_x;
	double	new_y;

	if (cub->map->initial_dir == 'W' || cub->map->initial_dir == 'E')
	{
		perp_dir[0] = cub->dir[1];
		perp_dir[1] = -cub->dir[0];
	}
	else
	{
		perp_dir[0] = -cub->dir[1];
		perp_dir[1] = cub->dir[0];
	}
	new_x = cub->pos[0] + 0.01 * perp_dir[0];
	new_y = cub->pos[1] + 0.01 * perp_dir[1];
	if (cub->map->layout[(int)new_y][(int)new_x] != '1' && \
	cub->map->layout[(int)new_y][(int)new_x] != '2')
	{
		cub->pos[0] = new_x;
		cub->pos[1] = new_y;
	}
}
