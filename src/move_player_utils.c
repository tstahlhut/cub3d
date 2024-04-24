/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:17:07 by leschenb          #+#    #+#             */
/*   Updated: 2024/04/23 14:33:44 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	move(t_cub *cub, double distance)
{
	double	new_x;
	double	new_y;

	new_x = cub->pos[0] + distance * cub->dir[0];
	new_y = cub->pos[1] + distance * cub->dir[1];
	if (cub->map->layout[(int)new_y][(int)new_x] == '2')
	{
		printf("YOU FOUND THE EXIT\n");
		cub->exit_found = 1;
	}
	if (cub->map->layout[(int)new_y][(int)new_x] != '0')
	{
		return ;
	}
	else
	{
		cub->pos[0] = new_x;
		cub->pos[1] = new_y;
	}
}

void	move_down(t_cub *cub)
{
	move(cub, -0.01);
}

void	move_up(t_cub *cub)
{
	move(cub, 0.01);
}
