/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcolorad <rcolorad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:52:47 by rcolorad          #+#    #+#             */
/*   Updated: 2024/05/27 17:46:08 by rcolorad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_store(char *store)
{
	char	*aux;
	int		len;
	
	len = 0;
	while (store[len] != '\0' && store[len] != '\n')
		len++;
	if (store[len] == '\n')
		len++;
	aux = ft_strdup(store + len);
	free(store);
	if (!aux)
		return (NULL);
	return (aux);
}

static char	*read_file(int fd, char *store)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(store);
			store = NULL;
			return (NULL);
		}
		store = ft_strjoin(store, buffer);
	}
	free(buffer);
	return (store);
}

static char	*get_line(char *store)
{
	char	*line;
	int		len;
	
	len = 0;
	if (!store || store[len] == '\0')
		return (NULL);
	while (store[len] && store[len] != '\n')
		len++;
	if (store[len] == '\n')
		len++;
	line = ft_calloc(sizeof(char), len + 1);
	if (!line)
		return (NULL);
	len = 0;
	while (store[len] && store[len] != '\n')
	{
		line[len] = store[len];
		len++;
	}
	if (store[len] == '\n')
		line[len] = store[len];
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(store), NULL);
	store = read_file(fd, store);
	if (!store)
		return (NULL);
	line = get_line(store);
	if (!line)
	{
		if (store)
		{
			free(store);
			store = NULL;
			return (NULL);
		}
	}
	store = free_store(store);
	return (line);
}


int	main(void)
{
	int	fd;
	char *line;

	fd = open("quijote.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
