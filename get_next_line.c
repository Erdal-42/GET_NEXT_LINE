/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elraira- <elraira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 10:39:55 by elraira-          #+#    #+#             */
/*   Updated: 2021/09/05 14:05:59 by elraira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void print_message(char *str)
{
	while (*str)
		write(2, str ++, 1);
}

void	exit_program(char *reserve)
{
	free (reserve);
	exit (EXIT_FAILURE);
}

int	present_nl(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*(str ++) == '\n')
			return (1);
	}
	return (0);
}

char	*ft_get_line(char *reserve)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (reserve[i])
	{
		if (reserve[i] == '\n')
			break ;
		++ i;
	}
	line = malloc(sizeof(*line) * (i + 1));
	if (!line)
	{
		print_message("error: Unable to allocate memory.");
		exit_program(reserve);
	}
	j = 0;
	while (j <= i)
	{
		line[j] = reserve[j];
		++ j;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_save(char *reserve)
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
    while (reserve[i])
        ++ i;
    leftover = malloc(sizeof(*leftover) * (i - mark + 1));
    if (!leftover)
        exit_program(reserve);
		//return (NULL);
    j = 0;
    while (mark < i)
        leftover[j ++] = reserve[mark ++];
    free(reserve);
    leftover[j] = '\0';
    return (leftover);
}

char	*ft_read_and_save(int fd, char *reserve)
{
	char	*buffer;	//ok
	int		size;		//ok

	buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1)); //ok
	if (!buffer)
	{
		print_message("error: Unable to allocate memory.");
		exit_program(reserve);
	}		//ok
	size = read(fd, buffer, BUFFER_SIZE);
	if (size < 1)
	{
		free (buffer);
		return (NULL);
	}
	buffer[size] = '\0';
	while (size > 0)
	{
		reserve = ft_strjoin(reserve, buffer);
		if (!reserve)
			exit_program(reserve);
		if (present_nl(reserve))
			break;
		size = read(fd, buffer, BUFFER_SIZE);
		buffer[size] = '\0';
	}
	free(buffer);	//ok
	return (reserve);	//ok
}


char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = ft_read_and_save(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	save = ft_save(save);
	return (line);
}




