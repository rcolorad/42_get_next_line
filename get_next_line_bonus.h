#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

# define MAX_FD 1024
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

char  *get_next_line(int fd);
char  *ft_strdup(char *s);
size_t  ft_strlen(char *s);
char  *ft_substr(char *s, unsigned int start, size_t len);
char  *ft_strjoin(char *s1, char *s2);
char  *ft_strchr(char *s, int c);

#endif