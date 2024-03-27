#include "get_next_line.h"
#include <string.h>

char	*get_next_line(int fd)
{
  char  *line;

  line = (char *) ft_calloc(5 , sizeof(char));
  read(fd, line, 5);
  return (line);
}


int main(void)
{
  int fd;
  int chars_read;
  char  buf[5];

  fd = open("test.txt", O_RDONLY);
  while (chars_read != 0)
  {
    strcpy(buf, get_next_line(fd));
    chars_read = strlen(buf);
    printf("%s", buf);
  }
  return (0);
}
