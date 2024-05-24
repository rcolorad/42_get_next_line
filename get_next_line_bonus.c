/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcolorad <rcolorad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:52:03 by rcolorad          #+#    #+#             */
/*   Updated: 2024/05/24 18:05:27 by rcolorad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*fill_store(int fd, char *store, char *buffer)
{
	ssize_t	bytes;

	bytes = 1;
	if (!store)
		store = ft_strdup("");
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		store = ft_strjoin(store, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (store);
}

static char	*get_new_store(char *store)
{
	int		len;
	int		i;
	char	*new_store;

	len = 0;
	i = 0;
	if (store == NULL)
		return (NULL);
	while (store[len] != '\n' && store[len])
		len++;
	if (store[len] == '\n')
		len++;
	new_store = (char *)malloc((ft_strlen(store) - len + 1) * sizeof(char));
	if (!new_store)
		return (NULL);
	while (store[len + i])
	{
		new_store[i] = store[len + i];
		i++;
	}
	free(store);
	new_store[i] = '\0';
	return (new_store);
}

static char	*get_line(char *store, char *line)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (store == NULL)
		return (NULL);
	while (store[len] != '\n' && store[len])
		len++;
	if (store[len] == '\n')
		len++;
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = store[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*store[MAX_FD];
	char		*buffer;
	char		*line;

	line = NULL;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(store[fd]);
		free(buffer);
		buffer = NULL;
		store[fd] = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	store[fd] = fill_store(fd, store[fd], buffer);
	if (*store[fd] == '\0')
	{
		free(store[fd]);
		return (store[fd] = 0);
	}
	line = get_line(store[fd], line);
	store[fd] = get_new_store(store[fd]);
	return (line);
}
/*
int	main(void)
{
	int	fd1;
	int fd2;
	int fd3;
	char *line;

	fd1 = open("text.txt", O_RDONLY);
	fd2 = open("text2.txt", O_RDONLY);
	fd3 = open("text3.txt", O_RDONLY);
	if (fd1 < 0)
	{
		perror("Error opening file 1");
		return (1);
	}
	if (fd2 < 0)
	{
		perror("Error opening file 2");
		return (1);
	}
	if (fd3 < 0)
	{
		perror("Error opening file 3");
		return (1);
	}
	int i = 0;
	while (i < 6)
	{
		line = get_next_line(fd1);
		printf("%s", line);
		free(line);
		line = get_next_line(fd2);
		printf("%s", line);
		free(line);
		line = get_next_line(fd3);
		printf("%s", line);
		free(line);
		i++;
	}
	while (i < 12)
	{
		line = get_next_line(fd1);
		printf("%s", line);
		free(line);
		line = get_next_line(fd2);
		printf("%s", line);
		free(line);
		line = get_next_line(fd3);
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
*/