#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

char  *get_next_line(int fd);
void  *ft_calloc(size_t count, size_t size);
#endif
