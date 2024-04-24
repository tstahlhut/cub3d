/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:20:28 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/24 11:37:33 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/* render_wall_texture: put vertical line with textured wall to image
	1. calculations
		1. calculates the corresponding x coordinate of the texture
		2. step
		3. tex_pos
	2. puts ceiling color (C->color) until start of wall
	3. puts texture pixels until wall ends
	4. puts floor color (F->color) pixels until end of screen 
	*/

void	render_wall_texture(t_cub *cub, int x, int tex)
{
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				y;

	tex_x = calculate_tex_x(cub, cub->walldist, tex);
	step = 1.0 * cub->map->tex_height[tex] / cub->wallheight;
	tex_pos = (cub->startwall - SCREEN_HEIGHT / 2 + cub->wallheight / 2) * step;
	y = -1;
	while (++y < cub->startwall) 
		my_pixel_put(cub->img, x, y, conv_rgb_hex(cub->map->c_color));
	while (y < cub->endwall)
	{
		tex_y = (int)tex_pos & (cub->map->tex_height[tex] - 1);
		tex_pos += step;
		my_pixel_put(cub->img, x, y, cub->map->texture[tex]
		[cub->map->tex_height[tex] * tex_y + tex_x]);
		y++;
	}
	y = cub->endwall - 1;
	while (++y < SCREEN_HEIGHT)
		my_pixel_put(cub->img, x, y, conv_rgb_hex(cub->map->f_color));
}

/* render_3d_view renders the players perspective on the 2D map in 3D
The rendering is done by raycasting. 
The raycasting calculations are based on:
	 https://lodev.org/cgtutor/raycasting.html
Lodev's calculation relies solely on vectors and triangles 
	(no pi or fisheye correction needed).
Rays are casted from the players position (x = cub->pos[0] & y = cub->pos[1]).
Depending on where and at what distance a wall is hit by the ray,
	the wall is depicted in what appears as 3D. 
As the map is in 2D, we only have to loop through the x-coordinates	of the screen
	(every vertical line and not every pixel of the screen) which makes it fast.
	For every x of the screen:
	1. the casted ray is calculated
	2. when and where a wall was hit
	3. depending on which wall was hit, the right texture (color) is chosen
	4. how high the wall has to be drawn based on its distance to the player
	5. the line (all y's of the screen for that x) is drawn 
		(put into a buffered image)
Variables used, shortly explained:
	1. tex: texture (i.e. colour) for that wall	*/

int	render_3d_view(t_cub *cub)
{
	int		x;
	int		tex;
	int		wall_type;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		calculate_ray(cub, x);
		wall_type = calculate_wall_hit(cub);
		tex = choose_texture(cub, wall_type);
		if (cub->side != 0 && cub->side != 1)
			printf("ERROR: side value wrong, see raycasting\n");
		calculate_wall_dimensions(cub);
		render_wall_texture(cub, x, tex);
		x++;
	}
	return (0);
}

/* render draw vertical line on screen */

/*void	render_wall_color(t_cub *cub, int x)
{
	int		color;
	int		y;

	color = LAVENDER;
	if (cub->side == 1)
		color = color / 2; //gives x and y side different brightness
	y = -1;
	while (++y < cub->startwall) 
		my_pixel_put(cub->img, x, y, conv_rgb_hex(cub->map->c_color));
	while (y < cub->endwall)
	{
		my_pixel_put(cub->img, x, y, color);
		y++;
	}
	while (y < SCREEN_HEIGHT) 
	{
		my_pixel_put(cub->img, x, y, conv_rgb_hex(cub->map->f_color));
		y++;
	}
}*/
