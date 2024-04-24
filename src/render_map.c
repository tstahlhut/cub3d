/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:07:44 by leschenb          #+#    #+#             */
/*   Updated: 2024/04/24 14:47:56 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/*
void	render_square(t_cub *cub, int x, int y, unsigned int color)
{
	int	px_start;
	int	py_start;
	int	px_end;
	int	py_end;
	int	px;
	int	py;

	px_start = x * SQUARE_SIZE;
	py_start = y * SQUARE_SIZE;
	px_end = (x + 1) * SQUARE_SIZE;
	py_end = (y + 1) * SQUARE_SIZE;
	py = py_start;
	while (py <= py_end)
	{
		px = px_start;
		while (px <= px_end)
		{
			render_pixel(cub, px, py, px_start, px_end, \
			py_start, py_end, color);
			px++;
		}
		py++;
	}
}
*/
/*
void ft_draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1)
	{
		my_pixel_put(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	render_player(t_cub *cub, int start_x, int start_y)
{
	int	x_pixel;
	int	y_pixel;
	int	end_x_pixel;
	int	end_y_pixel;
	int	i;

	i = 0;
	x_pixel = (start_x * 25) + (25 * cub->pos[0]);
	y_pixel = (start_y * 25) + (25 * cub->pos[1]);
	end_x_pixel = x_pixel + (cub->dir[0] * 10);
	end_y_pixel = y_pixel + (cub->dir[1] * 10);
	my_pixel_put(cub->img, x_pixel + i, y_pixel + i, YELLOW);
	ft_draw_line(cub->img, x_pixel, y_pixel, end_x_pixel, end_y_pixel, YELLOW);
}
*/

void	render_square(t_cub *cub, int x, int y, unsigned int color)
{
	int	px_end;
	int	py_end;
	int	px;
	int	py;

	px_end = (x + 1) * SQUARE_SIZE;
	py_end = (y + 1) * SQUARE_SIZE;
	py = y * SQUARE_SIZE - 1;
	while (++py < py_end)
	{
		px = x * SQUARE_SIZE - 1;
		while (++px <= px_end)
		{
			if (py == (y * SQUARE_SIZE) || py == py_end 
				|| px == (x * SQUARE_SIZE) || px == px_end)
			{
				if (color == WHITE)
					my_pixel_put(cub->img, px, py, BLACK);
				else if (color == BLACK)
					my_pixel_put(cub->img, px, py, WHITE);
			}
			else
				my_pixel_put(cub->img, px, py, color);
		}
	}
}

void	render_player(t_cub *cub, int start_x, int start_y)
{
	int	x_pixel;
	int	y_pixel;
	int	i;

	i = -2;
	x_pixel = (start_x * 25) + (25 * cub->pos[0]);
	y_pixel = (start_y * 25) + (25 * cub->pos[1]);
	while (i < 3)
	{
		my_pixel_put(cub->img, x_pixel, y_pixel + i, YELLOW);
		i++;
	}
	i = -2;
	while (i < 3)
	{
		my_pixel_put(cub->img, x_pixel + i, y_pixel, YELLOW);
		i++;
	}
}

void	render_minimap(t_cub *cub, int start_x, int start_y)
{
	int	x;
	int	y;

	y = start_y;
	while (y < (start_y + cub->map->nlines))
	{
		x = start_x;
		while (x < (start_x + cub->map->max_line_len))
		{
			if (cub->map->layout[y - start_y][x - start_x] == '1')
				render_square(cub, x, y, WHITE);
			if (cub->map->layout[y - start_y][x - start_x] == '2')
				render_square(cub, x, y, GREEN);
			else if (cub->map->layout[y - start_y][x - start_x] != '1' \
			&& cub->map->layout[y - start_y][x - start_x] != '2')
				render_square(cub, x, y, BLACK);
			x++;
		}
		y++;
	}
	render_player(cub, start_x, start_y);
}
