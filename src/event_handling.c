/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:11:00 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/24 11:38:27 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	key_press(int key, t_cub *cub)
{
	if (key == KEY_ESC)
		x_close(cub);
	else if (key == KEY_W)
		cub->m_flag.move_up = 1;
	else if (key == KEY_S)
		cub->m_flag.move_down = 1;
	else if (key == KEY_A)
		cub->m_flag.move_left = 1;
	else if (key == KEY_D)
		cub->m_flag.move_right = 1;
	else if (key == KEY_LEFT)
		cub->m_flag.look_left = 1;
	else if (key == KEY_RIGHT)
		cub->m_flag.look_right = 1;
	else if (key == KEY_M)
		cub->m_flag.map_flag ^= 1; 
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key == KEY_W)
		cub->m_flag.move_up = 0;
	else if (key == KEY_S)
		cub->m_flag.move_down = 0;
	else if (key == KEY_A)
		cub->m_flag.move_left = 0;
	else if (key == KEY_D)
		cub->m_flag.move_right = 0;
	else if (key == KEY_LEFT)
		cub->m_flag.look_left = 0;
	else if (key == KEY_RIGHT)
		cub->m_flag.look_right = 0;
	return (0);
}

/* x_close: This function closes the window with a MLX function. */

int	x_close(t_cub *cub)
{
	free_map_data(cub->map);
	close_window(cub);
	return (0);
}
