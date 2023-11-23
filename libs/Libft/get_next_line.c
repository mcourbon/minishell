/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:30:59 by momaiouf          #+#    #+#             */
/*   Updated: 2023/04/04 14:57:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_nbread_and_linebreak(char *str, int nb_read)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (0);
	if (nb_read == 0)
		return (1);
	while (str[i] != 0)
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_file(int fd, char *backup)
{
	int		nb_read;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	nb_read = 1;
	while (!check_nbread_and_linebreak(backup, nb_read))
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[nb_read] = '\0';
		backup = ft_strjoin_free(backup, buffer);
		if (backup == NULL)
			return (NULL);
	}
	free(buffer);
	return (backup);
}

char	*get_a_line(char *backup)
{
	int		i;
	int		len_line;
	char	*line;

	i = 0;
	if (!backup[i])
		return (NULL);
	len_line = get_len_line(backup);
	line = malloc(sizeof(char) * (len_line + 1));
	if (line == NULL)
		return (NULL);
	while (backup[i] && backup[i] != '\n')
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		line[i] = backup[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line_start(char *backup)
{
	int		i;
	int		j;
	int		len_next_buffer;
	char	*next_buffer;

	i = get_index_linebreak(backup);
	j = 0;
	if (backup[i] == '\0')
		return (free(backup), NULL);
	len_next_buffer = ft_strlen(backup) - i;
	next_buffer = malloc(sizeof(char) * (len_next_buffer));
	if (next_buffer == NULL)
		return (NULL);
	i++;
	while (backup[i])
	{
		next_buffer[j] = backup[i];
		i++;
		j++;
	}
	next_buffer[j] = '\0';
	free(backup);
	return (next_buffer);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_file(fd, buffer);
	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	line = get_a_line(buffer);
	buffer = get_next_line_start(buffer);
	return (line);
}
