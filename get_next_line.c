#include "get_next_line.h"
#include <sys/types.h>

static char *get_line(int fd, char *buffer, char *chars_left)
{
  ssize_t bytes_read;
  char  *temporal;

  bytes_read = 1;
  while (bytes_read > 0)
  {
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read == -1)
    {
      free(buffer);
      return (NULL);
    }
    else if (bytes_read == 0)
      break;
    buffer[bytes_read] = 0;
    if (!buffer)
      buffer = ft_strdup("");
    temporal = buffer;
    buffer = ft_strjoin(temporal, buffer);
    free(temporal);
    temporal = NULL;
    if (ft_strchr(buffer, '\n'))
      break;
  }
  return(buffer);
}

static char *set_line(char *line_read)
{
  char  *buffer;
  ssize_t i;
  
  i = 0;
  while (line_read[i] != '\n' && line_read[i] != '\0')
    i++;
  if (line_read[i] == '\0' || line_read[1] == '\0')
    return (NULL);
  buffer = ft_substr(line_read, i + 1, ft_strlen(line_read) - i);
  if (*buffer == 0)
  {
    free(buffer);
    buffer = NULL;
  }
  line_read[i + 1] = '\0';
  return (buffer);
}

char	*get_next_line(int fd)
{
  static char *chars_left;
  char  *buffer;
  char  *line;

  line = NULL;
  buffer = (char *) malloc ((BUFFER_SIZE + 1) * sizeof(char));
  if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
  {
    free(chars_left);
    free(buffer);
    buffer = NULL;
    chars_left = NULL;
    return (NULL);
  }
  if (!buffer)
    return(NULL);
  line = get_line(fd, buffer, chars_left);
  free(buffer);
  if (!line)
    return (NULL);
  chars_left = set_line(line);
  return (line);
}

