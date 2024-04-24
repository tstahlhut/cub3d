/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:44:54 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/22 14:17:46 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	start_timer(t_cub *cube)
{
	cube->timer = time(NULL);
}

long	ft_get_time(t_cub *cube)
{
	static long	elapsed_time;
	time_t		current_time;

	if (cube->exit_flag)
	{
		current_time = time(NULL);
		elapsed_time = current_time - cube->timer;
	}
	return (elapsed_time);
}

void	print_timer(t_cub *cub)
{
	long	min;
	long	sec;

	if (!cub->exit_flag)
		return ;
	min = ft_get_time(cub) / 60;
	sec = ft_get_time(cub) % 60;
	if (cub->exit_found)
		printf("IN ");
	if (min < 10)
		printf("0%li:", min);
	else
		printf("%li:", min);
	if (sec < 10)
		printf("0%li\n", sec);
	else
		printf("%li\n", sec);
}
