/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:18:16 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/24 15:35:34 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/* render_frame: game loop which renders game
	1. if the exit was found, the exit screen is rendered and function exits
	2. if player was moved, new player positions are calculated
	3. 3D game image is rendered
	4. minimap is rendered (on and off with key 'M')
	5. timer is printed in terminal if there is an exit door in map
	6. current window is cleared
	7. rendered image is put to window*/

int	render_frame(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub->exit_found > 0)
		return (exit_screen(cub), 0);
	if (cub->m_flag.move_up == 1)
		move_up(cub);
	if (cub->m_flag.move_down == 1)
		move_down(cub);
	if (cub->m_flag.move_left == 1)
		move_left(cub);
	if (cub->m_flag.move_right == 1)
		move_right(cub);
	if (cub->m_flag.look_left == 1)
		look_left(cub);
	if (cub->m_flag.look_right == 1)
		look_right(cub);
	render_3d_view(cub);
	if (cub->m_flag.map_flag == 1) 
		render_minimap(cub, set_right(cub), set_down(cub));
	print_timer(cub);
	mlx_clear_window(cub->mlx, cub->win);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img->img, 0, 0);
	return (0);
}

/* game_loop: hooks events
	1. key press events are hooked
	2. key release events are hooked
	3. program exits when cross on window is clicked
	4. loops through game loop (render frame function)*/

void	game_loop(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 17, 0L, x_close, cub);
	mlx_loop_hook(cub->mlx, render_frame, cub);
	mlx_loop(cub->mlx);
}

/* main:
	1. number of arguments is checked (1 argument required)
	2. main struct cub is initialized
	3. map is read and put to struct map
	4. mlx window is opened
	5. timer is started if map has an exit door (2)
	6. game loop starts (ends with ESC or clicking cross on window)*/

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc < 2)
		return (printf("No map given. Choose one from ./maps/\n"), 0);
	if (argc > 2)
		return (printf("Too many arguments. 1 argument required.\n"), 0);
	init_cub(&cub);
	if (initmap(argv[1], &cub) == -1)
		error_exit(&cub, "could not initialize map", NULL);
	open_window(&cub);
	start_timer(&cub);
	game_loop(&cub);
}
