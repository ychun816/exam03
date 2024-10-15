#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdio.h>

// #ifndefine BUFFER_SIZE 
# define BUFFER_SIZE 42
// #endif

char *get_next_line(int fd);

#endif