/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:16:20 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/24 11:37:13 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	my_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x > SCREEN_WIDTH || y > SCREEN_HEIGHT)
		return ;
	pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	render_image(t_cub *cub, t_img *img)
{
	int	x;
	int	y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			my_pixel_put(cub->img, x, y, GREY);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, img->img, 0, 0);
}

/*void	render_player(t_cub *cub)
{
	int	px;
	int	py;
	int	px_end;
	int	py_end;

	printf("player's position is: %i, %i\n", cub->pos[0], cub->pos[1]);
	mlx_clear_window(cub->mlx, cub->win);
	py = cub->pos[1] * (SQUARE_SIZE / 10);
	py_end = cub->pos[1] * (SQUARE_SIZE / 10) + (SQUARE_SIZE / 10);
	px_end = cub->pos[0] * (SQUARE_SIZE / 10) + (SQUARE_SIZE / 10);
	while (py <= py_end)
	{
		px = cub->pos[0] * (SQUARE_SIZE / 10);
		while (px <= px_end)
		{
			my_pixel_put(cub->img, px, py, YELLOW);
			px++;
		}
		py++;
	}
}*/