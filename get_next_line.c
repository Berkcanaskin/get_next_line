/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:23:06 by baskin            #+#    #+#             */
/*   Updated: 2024/11/25 18:49:53 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*my_malloc(int n)
{
	char	*str;

	str = malloc(sizeof(char) * n);
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_creat(int fd, char *buffer)
{
	char	*temp;
	int		size;

	temp = my_malloc((BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	size = 1;
	while (!ft_strchr(buffer) && size != 0)
	{
		size = read(fd, temp, BUFFER_SIZE);
		if (size == -1)
			return (free(temp), NULL);
		temp[size] = '\0';
		buffer = ft_strjoin(buffer, temp);
	}
	return (free(temp), buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = ft_creat(fd, buffer);
	if (!buffer)
		return (NULL);
	return (line = ft_line(buffer), buffer = ft_new_str(buffer), line);
}
