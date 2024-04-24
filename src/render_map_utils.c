/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:52:42 by leschenb          #+#    #+#             */
/*   Updated: 2024/04/24 12:07:26 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	set_right(t_cub *cube)
{
	return (SCREEN_WIDTH / SQUARE_SIZE - cube->map->max_line_len);
}

int	set_down(t_cub *cube)
{
	return (SCREEN_HEIGHT / SQUARE_SIZE - cube->map->nlines);
}
