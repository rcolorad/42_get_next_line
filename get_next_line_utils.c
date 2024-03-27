#include "get_next_line.h"

void  *ft_calloc(size_t count, size_t size)
{
  char  *a;
  size_t  i;

  i = 0;
  a = (char *) malloc(count * size);
  if (!a)
    return (0);
  while (i < count * size)
  {
    a[i] = 0;
    i++;
  }
  return (a);
}
