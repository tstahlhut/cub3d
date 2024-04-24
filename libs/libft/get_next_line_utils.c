/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:03:58 by leschenb          #+#    #+#             */
/*   Updated: 2024/04/24 13:23:24 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_get_the_spare(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i] != '\n')
		i++;
	i = i + 1;
	j = 0;
	while (i < BUFFER_SIZE)
	{
		buffer[j] = buffer[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
}

char	*ft_line_results(int ret, char *stock, char *buffer)
{
	char		*line;

	line = NULL;
	if (ft_strlen(stock) == 0)
	{
		free(stock);
		return (NULL);
	}
	line = ft_get_the_line(stock);
	if (ret > 0)
		ft_get_the_spare(buffer);
	free(stock);
	return (line);
}

char	*gnlft_strjoin(char *left_str, char *buff)
{
	int		i;
	int		l;
	char	*str;

	l = 0;
	i = 0;
	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	str = malloc (sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	while (left_str[i] != '\0')
	{
		str[i] = left_str[i];
		i++;
	}
	while (buff[l] != '\0')
		str[i++] = buff[l++];
	str[i] = '\0';
	free(left_str);
	return (str);
}

char	*gnlft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
