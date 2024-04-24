/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:40:46 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/19 13:52:16 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/*  calculate_ray: calculates ray for given x of the screen
		for x and y direction of the grid (map)
	1. calculate ray position and direction (raydir)
		cam_x is the x-coordinate of the camera plane
	2. calculate length of ray from one x- or y-side to next (deltadist)
		to avoid undefined behaviour if ray_dir = 0 (division through 0),
		deltadist is in that case infinity */

void	calculate_ray(t_cub *cub, int x)
{
	double	cam_x;
	int		i;

	i = 0;
	while (i < 2)
	{
		cam_x = 2 * x / (double)SCREEN_WIDTH - 1;
		cub->raydir[i] = cub->dir[i] + cub->camplane[i] * cam_x;
		if (cub->raydir[i] != 0)
			cub->deltadist[i] = fabs(1 / cub->raydir[i]);
		else
			cub->deltadist[i] = INFINITY;
		i++;
	}
}

/* calculate step and initial sidedist for x (i = 0) and y (i = 1)
	1. step: in which direction the ray is casted (north, south, west or east)
		if raydir is negative, step is -1 (left for x (i = 0) or up for y (i = 1))
		otherwise step is 1 (right for x, down for y)
	2. initial sidedist: distance from player to first x or y side of grid (map)
		sidedist[0]: distance the ray has to travel to the first x-side 
		sidedist[1]: distance the ray has to travel to the first y-side */

void	calculate_step_sidedist(t_cub *cub, int map[2])
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (cub->raydir[i] < 0)
		{
			cub->step[i] = -1;
			cub->sidedist[i] = (cub->pos[i] - map[i]) * cub->deltadist[i];
		}
		else
		{
			cub->step[i] = 1;
			cub->sidedist[i] = (map[i] + 1.0 - cub->pos[i]) * cub->deltadist[i];
		}
		i++;
	}
}

/* calculate_wall_hit: calculates where ray hits wall 
	while hit = 0, no wall was hit and the loop continues
	as soon as hit = 1, the function exits.
	The side which was hit (x = 0 or y = 1) is stored in cub->side.
	Variables explained:
		1. map[]: in which square on the map the ray is currently in
			it starts at the players position
		2. deltadist[2]: length of ray from one x- or y-side 
			to next x- or y-side of a square on the map
*/	

int	calculate_wall_hit(t_cub *cub)
{
	int	hit;
	int	map[2];
	int	i;

	map[0] = (int)cub->pos[0];
	map[1] = (int)cub->pos[1];
	calculate_step_sidedist(cub, map);
	hit = 0;
	while (hit == 0)
	{
		if (cub->sidedist[0] < cub->sidedist[1])
			i = 0;
		else
			i = 1;
		cub->sidedist[i] += cub->deltadist[i];
		map[i] += cub->step[i];
		cub->side = i;
		if (cub->map->layout[map[1]][map[0]] != 48)
			hit = 1;
	}
	return (cub->map->layout[map[1]][map[0]]);
}

/* calculates the dimensions of the wall that was hit
	1. wallheight: height of line drawn on screen, i.e. height of wall
	2. walldist: perpendicular distance from camera plane to wall
	3. startwall: where wall texture should start (pixel line on screen)
	4. endwall: where wall texture should end (pixel line  on screen)
		*/

void	calculate_wall_dimensions(t_cub *cub)
{
	cub->walldist = (cub->sidedist[cub->side] - cub->deltadist[cub->side]);
	cub->wallheight = (int)(SCREEN_HEIGHT / cub->walldist);
	cub->startwall = -cub->wallheight / 2 + SCREEN_HEIGHT / 2;
	if (cub->startwall < 0)
		cub->startwall = 0;
	cub->endwall = cub->wallheight / 2 + SCREEN_HEIGHT / 2;
	if (cub->endwall >= SCREEN_HEIGHT || cub->endwall < 0)
		cub->endwall = SCREEN_HEIGHT - 1;
}

/* calculate the x-coordinate of the texture (tex_x) and returns it
	wall: calculate where exactly wall was hit by ray 
		floor is a function in math.h which returns wall as an integral */

int	calculate_tex_x(t_cub *cub, double walldist, int tex)
{
	double	wall;
	int		tex_x;

	if (cub->side == 0)
		wall = cub->pos[1] + walldist * cub->raydir[1];
	else
		wall = cub->pos[0] + walldist * cub->raydir[0];
	wall -= floor(wall);
	tex_x = (int)(wall * (double)cub->map->tex_width[tex]);
	if (cub->side == 0 && cub->raydir[0] > 0)
		tex_x = cub->map->tex_width[tex] - tex_x - 1;
	if (cub->side == 1 && cub->raydir[1] < 0)
		tex_x = cub->map->tex_width[tex] - tex_x - 1;
	return (tex_x);
}
