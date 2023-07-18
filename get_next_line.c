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

char	*ft_get_line(char *reserve)
{
    int     i;
    int     j;
    char    *line;

    if (reserve[0] == '\0')
        return (NULL);
    i = 0;
    //we have a non NULL string
    while (reserve[i])
    {
        //we need to count characters upto null or including newline
        if (reserve[i ++] == '\n')
            break ;
    }
    //then we allocate string space equal to count;
    line = malloc(sizeof(*line) * (i + 1));
    if (!line)
    {
        print_message("error: Unable to allocate memory.");
		exit_program(reserve);
    }
    //we copy characters from parameter to new string equal to count
    j = 0;
    while (j < i)
    {
        line[j] = reserve[j];
        ++ j;
    }
    //we append a NULL character to the new string.
    line[j] = '\0';
    //we return the new string.
    return (line);   
}

char	*ft_save(char *save)
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
		free(reserve)
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

char	*ft_read_and_save(int fd, char *save)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return (save);
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
