/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:58:41 by leschenb          #+#    #+#             */
/*   Updated: 2024/04/24 14:33:17 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	allocate_map_data(t_cub *cub)
{
	t_map	*map;

	cub->map = malloc(sizeof(t_map));
	set_map_data_to_null(cub->map);
	if (!cub->map)
		error_exit(cub, "malloc failed", NULL);
	map = cub->map;
	map->max_line_len = 0;
	map->nlines = 0;
	map->f_color = (t_rgb *)malloc(sizeof(t_rgb));
	if (!map->f_color)
		error_exit(cub, "malloc failed", NULL);
	map->c_color = (t_rgb *)malloc(sizeof(t_rgb));
	if (!map->c_color)
		error_exit(cub, "malloc failed", NULL);
}

char	*moded_strdup(const char *s)
{
	int		i;
	int		len;
	char	*nstr;

	i = 0;
	len = 0;
	while (s[len] != '\0' && s[len] != '\n')
		len++;
	nstr = malloc(1 + len * sizeof(char));
	if (nstr == NULL)
	{
		return (NULL);
	}
	while (i < len)
	{
		nstr[i] = s[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}

int	check_valid_format(char *str)
{
	int	i;
	int	comm_counter;

	i = 0;
	comm_counter = 0;
	while (str[i] != '\n')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == 'F' || str[i] == 'C')
			i++;
		if (str[i] == ',')
			comm_counter++;
		if (str[i] != ' ' && str[i] != ',' \
		&& str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' \
		&& str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' \
		&& str[i] != '8' && str[i] != '9')
		{
			return (-1);
		}
		i++;
	}
	if (comm_counter != 2)
		return (-1);
	return (0);
}

void	ft_setcolor_f(t_cub *cube, char *line, int i)
{
	char	*newline;
	char	**ar;

	while (line[i] == 'F' || line[i] == ' ')
		i++;
	if (check_valid_format(line) == -1)
		cube->map->map_valid_flag = -1;
	newline = ft_strdup(line + i);
	ar = ft_split(newline, ',');
	if (ar[0] && ar[1] && ar[2])
	{
		cube->map->f_color->r = ft_atoi(ar[0]);
		cube->map->f_color->g = ft_atoi(ar[1]);
		cube->map->f_color->b = ft_atoi(ar[2]);
	}
	if (ar != NULL)
	{
		free(ar[0]);
		free(ar[1]);
		free(ar[2]);
		free(ar);
	}
	if (newline != NULL)
		free(newline);
}

void	ft_setcolor_c(t_cub *cube, char *line, int i)
{
	char	*newline;
	char	**ar;

	while (line[i] == 'C' || line[i] == ' ')
		i++;
	if (check_valid_format(line) == -1)
		cube->map->map_valid_flag = -1;
	newline = ft_strdup(line + i);
	ar = ft_split(newline, ',');
	if (ar[0] && ar[1] && ar[2])
	{
		cube->map->c_color->r = ft_atoi(ar[0]);
		cube->map->c_color->g = ft_atoi(ar[1]);
		cube->map->c_color->b = ft_atoi(ar[2]);
	}
	if (ar != NULL)
	{
		free(ar[0]);
		free(ar[1]);
		free(ar[2]);
		free(ar);
	}
	if (newline != NULL)
		free(newline);
}
