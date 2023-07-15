#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> 

#define BUFFER_SIZE	10

char	*read_line(int, char *);
char	*ft_strjoin(char *, char *);
int		ft_strlen(char *);
char	*get_line(char *);
char	*truncate(char *);

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

int	present_nl(char *str)
{
	while (*str)
	{
		if (*(str ++) == '\n')
			return (1);
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int i;

	if(!str)
		return (0);
	i = 0;
	while (str[i])
		++ i;
	return (i);
}

char *ft_strjoin(char *str1, char *str2)
{
	int 	len;
	char 	*unified;
	int		i;

	len = ft_strlen(str1) + ft_strlen(str2);
	unified = malloc(sizeof(*unified) * (len + 1));
	if (!unified)
	{
		free(str1);
		free(str2);
		print_message("error: unable to allocate memory.");
		return (NULL);
	}
	i = 0;
	if (str1)
	{
		while (str1[i])
		{
			unified[i] = str1[i];
			++ i;
		}
	}
	while (*str2)
		unified[i ++] = *(str2 ++);
	unified[i] = '\0';
	free(str1);
	free(str2);
	return (unified);
}

char	*read_line(int fd, char *reserve)
{
	char	*buffer;
	int		size;

	buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	if (!malloc)
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
		reserve = ft_strjoin(reserve, buffer); //I get error here on the second read.
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
