/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:23:53 by jlaine            #+#    #+#             */
/*   Updated: 2024/06/12 18:21:41 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_until_newline(int fd, char **buffer)
{
	ssize_t	bytes_read;
	char	*temp_buffer;

	bytes_read = 1;
	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (*buffer == NULL)
		*buffer = ft_strdup("");
	while (bytes_read && !ft_strchr(*buffer, '\n'))
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (temp_buffer);
			free (*buffer);
			*buffer = NULL;
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		*buffer = ft_strjoin(*buffer, temp_buffer);
	}
	free (temp_buffer);
	return (NULL);
}

char	*extract_line(char **buffer)
{
	char	*new_buffer;
	char	*line;

	if (!ft_strchr(*buffer, '\n'))
	{
		line = ft_strdup(*buffer);
		free (*buffer);
		*buffer = NULL;
	}
	else
	{
		line = ft_substr(*buffer, 0, ft_strchr(*buffer, '\n') - *buffer + 1);
		new_buffer = ft_strdup(ft_strchr (*buffer, '\n') + 1);
		free (*buffer);
		*buffer = new_buffer;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line_read;

	line_read = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	read_until_newline(fd, &buffer[fd]);
	if (buffer[fd] && buffer[fd][0] != 0)
		line_read = extract_line(&buffer[fd]);
	if (buffer[fd] && buffer[fd][0] == 0)
	{
		free (buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line_read);
}
/*
int main(void)
{
  int	fd;
  char  *next_line;
  int  	count;

  count = 0;
  fd = open("example.txt", O_RDONLY);
  while (1)
  {
    next_line = get_next_line(fd);
    if (next_line == NULL)
      break ;
    count++;
    printf("[%d]:%s", count, next_line);
	free (next_line);
    next_line = NULL;
  }
  close(fd);
  return (0);
}
*/
