#ifndef GETNEXTLINE_H
# define GETNEXTLINE_H

#include <stdlib.h>
//#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
//#include "get_next_line_utils.c" 

//#define BUFFER_SIZE 5

char	*read_line(int, char *);
char	*ft_strjoin(char *, char *);
int		ft_strlen(char *);
char	*get_line(char *);
char	*ft_truncate(char *);
int     present_nl(char *);
void    print_message(char *);
char    *get_next_line(int);
#endif