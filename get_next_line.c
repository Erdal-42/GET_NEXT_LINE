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

	reserve = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
	{
		print_message("error: Invalid Parameter");
		return (NULL);
	}
	reserve = read_line(fd, reserve);
	if (!reserve)
		return (NULL);
	
	line = get_line(reserve);
	reserve = truncate(reserve);
	return (line);
}

char	*truncate(char *reserve)
{
	int 	i;
	char	*leftover;

	while (*reserve)
	{
		if (*(reserve ++) == '\n')
			break; 
	}
	i = 0;
	while (*(reserve ++))
		++ i;
	if (!i)
	{
		free(reserve);		
		return (NULL);
	}
	leftover = malloc(sizeof(*leftover) * (i + 1));
	if (!leftover)
	{
		print_message("error: unable to allocate memory.");
		exit_program(reserve);
	}
	i = 0;
	while (*reserve)
		leftover[i ++] = *(reserve ++);
	leftover[i] = '\0';
	free(reserve);
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
		print_message("error: unable to allocate memory.");
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
		print_message("error: unable to allocate memory.");
		exit_program(reserve);
	}
	size = read(fd, buffer, BUFFER_SIZE);
	buffer[size] = '\0';
	if (size < 1)
		return (NULL);
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

int	main()
{
	while (1)
		printf("%s", get_next_line(0));
	return (0);
}
