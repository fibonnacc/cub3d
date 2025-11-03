/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <helfatih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:05:50 by helfatih          #+#    #+#             */
/*   Updated: 2025/02/18 11:27:00 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_check(int fd, char *line, char *buffer)
{
	ssize_t	len_byte;
	char	*new_char;

	while (1)
	{
		len_byte = read(fd, buffer, BUFFER_SIZE);
		if (len_byte == -1)
			return (free(buffer), free(line), NULL);
		if (len_byte == 0)
			break ;
		buffer[len_byte] = '\0';
		if (!line)
			line = ft_strdup(buffer);
		else
		{
			new_char = line;
			line = ft_strjoin(line, buffer);
			free(new_char);
			if (!line || ft_my_strchr(line, '\n'))
				break ;
		}
	}
	free(buffer);
	return (line);
}

char	*check_my_line(char *line)
{
	int		i;
	char	*buffer;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	buffer = (char *)malloc(i + 2);
	if (!buffer)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		buffer[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		buffer[i] = line[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*check_new_line(char *line)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	i++;
	buffer = (char *)malloc(ft_strlen(line) - i + 1);
	if (!buffer)
		return (NULL);
	j = 0;
	while (line[i])
		buffer[j++] = line[i++];
	buffer[j] = '\0';
	free(line);
	line = NULL;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*next_line;
	char		*line1;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	next_line = read_check(fd, next_line, buffer);
	if (!next_line)
		return (NULL);
	line1 = check_my_line(next_line);
	next_line = check_new_line(next_line);
	if (*line1 == '\0')
	{
		free(line1);
		line1 = NULL;
	}
	return (line1);
}
