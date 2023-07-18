/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:39:55 by ekocak            #+#    #+#             */
/*   Updated: 2023/07/18 14:05:59 by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	exit_program(char *reserve)
{
	free (reserve);
	exit (EXIT_FAILURE);
}

/*
 * Prototype: 
 * char *get_next_line(int fd)
 * This is the program for reading the line
 * progressively from a file descriptor. Each
 * call progresses to the next line delimited by a 
 * newline or EOF.
 * Return: string line.
 */

char *get_next_line(int fd)
{
	static char	*reserve;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
	{
		print_message("error: Invalid Parameter");
		return (NULL);
	}
	if (!present_nl(reserve))
		reserve = read_line(fd, reserve);
	if (!reserve)
		return (NULL);
	line = get_line(reserve);
	reserve = ft_truncate(reserve);
	return (line);
}

/* 
 * Prototype: char    *ft_truncate(char *reserve)
 * This function trims the reserve string starting
 * from the beginning and upto and including the 
 * first newline. If the newline doesn't exist, in
 * that case reserve is emptied.
 * Return: the reserve after it is 
 * trimmed or emtied.  
 */

char    *ft_truncate(char *reserve)
{
    int     i;
    int     j;
    int     mark;
    char    *leftover;

    i = 0;
    while (reserve[i])
	{
        if (reserve[i ++] == '\n')
            break;
	}
	if (!reserve[i])
	{
		free(reserve);
		return (NULL);
	}
    mark = i ++;
    i = ft_strlen(reserve);
    if (!(leftover = malloc(sizeof(*leftover) * (i - mark + 1))))
        exit_program(reserve);
    j = 0;
    while (mark < i)
        leftover[j ++] = reserve[mark ++];
    leftover[j] = '\0';
    return (free(reserve), leftover);
}

/*
 * Prototype: 
 * char	*get_line(char *reserve)
 * This function returns upto and including the first
 * newline character from the reserve string accumulated
 * after reading from a file descriptor. If no newline
 * character is detected, then all characters until the
 * EOF is read. 
 * Return: char * line from the reserve.
 */

char	*get_line(char *reserve)
{
    int     i;
    int     j;
    char    *line;

    if (reserve[0] == '\0')
        return (NULL);
    i = 0;
    while (reserve[i])
	{
        if (reserve[i ++] == '\n')
            break ;
	}
    line = malloc(sizeof(*line) * (i + 1));
    if (!line)
    {
        print_message("error: Unable to allocate memory.");
		exit_program(reserve);
    }
    j = -1;
    while (++j < i)
	{
        line[j] = reserve[j];
	}
	line[j] = '\0';
    return (line);   
}

/*
 * Prototype: 
 * char	*read_line(int fd, char *reserve)
 * This function takes a file descriptor and reads from
 * the file descriptor. The read string is stored within
 * reserve. The reading process continues until a 
 * newline character is detected or end of file is
 * reached. 
 * Return: char * data read from the file descriptor.  
 */

char	*read_line(int fd, char *reserve)
{
	char	*buffer;
	int		size;

	if (!(buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1))))
	{
		print_message("error: Unable to allocate memory.");
		exit_program(reserve);
	}
	size = read(fd, buffer, BUFFER_SIZE);
	if (size < 0)
	{
		free (buffer);
		return (NULL);
	}
	buffer[size] = '\0';
	while (size > 0)
	{
		if (!(reserve = ft_strjoin(reserve, buffer)))
			exit_program(reserve);
		if (present_nl(reserve))
			break;
		size = read(fd, buffer, BUFFER_SIZE);
		buffer[size] = '\0';
	}
	return (free(buffer), reserve);
}