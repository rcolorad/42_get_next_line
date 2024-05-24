/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcolorad <rcolorad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:52:47 by rcolorad          #+#    #+#             */
/*   Updated: 2024/05/24 12:52:49 by rcolorad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*store;
	char		*buffer;
	char		*line;

	line = NULL;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(store);
		free(buffer);
		buffer = NULL;
		store = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	store = fill_store(fd, store, buffer);
	if (*store == '\0')
	{
		free(store);
		return (store = 0);
	}
	line = get_line(store, line);
	store = get_new_store(store);
	return (line);
}

/*
int	main(void)
{
	int	fd;
  char *line;

  fd = open("test.txt", O_RDONLY);
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
*/