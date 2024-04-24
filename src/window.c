/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:54:13 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/23 12:50:31 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	open_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		error_exit(cub, "connection to X-Server failed to establish", NULL);
	read_in_textures(cub, cub->map);
	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, NAME);
	if (!cub->win)
		error_exit(cub, "new window failed to open", NULL);
	init_img(cub, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void	close_window(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->img)
	{
		mlx_destroy_image(cub->mlx, cub->img->img);
		free(cub->img);
	}
	if (cub->img_exit.img)
	{
		mlx_destroy_image(cub->mlx, cub->img_exit.img);
	}
	if (cub->win && cub->mlx)
	{
		mlx_clear_window(cub->mlx, cub->win);
		mlx_destroy_window(cub->mlx, cub->win);
	}
	if (cub->mlx)
	{
		mlx_loop_end(cub->mlx);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	exit (0);
}
