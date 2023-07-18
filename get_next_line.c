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
