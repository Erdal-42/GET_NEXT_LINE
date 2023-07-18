#include "get_next_line.h"


void	exit_program(char *reserve)
{
	free (reserve);
	exit (EXIT_FAILURE);
}

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

char	*get_line(char *reserve)
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


char	*read_line(int fd, char *reserve)
{
	char	*buffer;
	int		size;

	buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		print_message("error: Unable to allocate memory.");
		exit_program(reserve);
	}
	size = read(fd, buffer, BUFFER_SIZE);
	buffer[size] = '\0';
	if (size < 1)
	{
		free (buffer);
		return (NULL);
	}
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
	free(buffer);
	return (reserve);
}
/*
int	main()
{
	int fd;
	char *str;

	fd = open("test.txt", O_RDONLY);
	while ((str = get_next_line(fd)) != NULL)
		printf("%s", str);
	close(fd);
	return (0);
}
*/