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
	static int	i = 1;

	reserve = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
	{
		print_message("error: Invalid Parameter");
		return (NULL);
	}
	if (!present_nl(reserve))
	{
		reserve = read_line(fd, reserve);
		printf("%d: Reserve: %s\n", i, reserve);
	}
	if (!reserve)
		return (NULL);
	
	line = get_line(reserve);
	printf("%d: Line: %s\n", i, line);
	reserve = ft_truncate(reserve);
	printf("%d: Truncated Reserve: %s\n", i, reserve);
	++ i;
	return (line);
}

char	*ft_truncate(char *reserve)
{
	int 	i;
	char	*leftover;

	printf("WITHIN TRUNCATE\n");
	while (*reserve)
	{
		if (*(reserve ++) == '\n')
			break; 
	}
	i = 0;
	printf("We should be after the newline: %s", reserve);
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
		print_message("error: Unable to allocate memory.");
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

int	main()
{
	int fd;

	fd = open("test.txt", O_RDONLY);
	while (printf("%s", get_next_line(fd) > 0))
		;
	close(fd);
	return (0);
}
