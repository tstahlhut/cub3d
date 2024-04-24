/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:02:48 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/24 17:35:23 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	free_textures(t_map *map)
{
	int	i;

	i = -1;
	while (++i < (TEX_NUM))
	{
		if (map->texture[i])
			free(map->texture[i]);
	}
}

/* free_ptr: frees a char* pointer and sets it to NULL*/

void	free_ptr(char *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

/* free_map_data: frees all allocated memory in map struct*/

void	free_map_data(t_map *map)
{
	int	i;

	if (map)
	{
		free_textures(map);
		free_ptr(map->no);
		free_ptr(map->ea);
		free_ptr(map->we);
		free_ptr(map->so);
		if (map->c_color != NULL)
			free(map->c_color);
		if (map->f_color != NULL)
			free(map->f_color);
		i = -1;
		if (map->layout)
		{
			while (map->nlines > ++i)
				free_ptr(map->layout[i]);
			free(map->layout);
			map->layout = NULL;
		}
		free(map);
		map = NULL;
	}
}

/* error_exit: clean exit of program when an error occurs
	1. prints error message
	2. frees map data
	3. closes all mlx images and windows
	4. exits with error code 1*/

void	error_exit(t_cub *cub, char *message, char *file)
{
	if (!file)
		printf("Error: %s\n", message);
	else
	{
		printf("Error: %s: %s\n", message, file);
		if (ft_strncmp(message, "double textures", 15) == 0)
		{
			free(file);
			file = NULL;
		}
	}
	free_map_data(cub->map);
	close_window(cub);
	exit(1);
}

/* exit_screen: render exit screen when player found exit door
	1. puts exit image to image
	2. destroys and frees previously used image (game image)
	3. puts new image to window*/

void	exit_screen(t_cub *cub)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	if (cub->exit_found == 1)
	{
		cub->img_exit.img = mlx_xpm_file_to_image(cub->mlx, EXIT_IMAGE, 
				&width, &height);
		if (!cub->img_exit.img)
		{
			error_exit(cub, "image could not be put to window", EXIT_IMAGE);
		}
		mlx_destroy_image(cub->mlx, cub->img->img);
		free(cub->img);
		cub->img = NULL;
		mlx_clear_window(cub->mlx, cub->win);
		mlx_put_image_to_window(cub->mlx, cub->win, cub->img_exit.img, 0, 0);
		cub->exit_found = 2;
	}
	return ;
}
