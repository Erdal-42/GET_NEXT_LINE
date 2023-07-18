#include "get_next_line.h"

void print_message(char *str)
{
	while (*str)
		write(2, str ++, 1);
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
	unified = (char *)malloc(sizeof(*unified) * (len + 1));
	if (!unified)
	{
		print_message("error: unable to allocate memory.");
		return (free(str1), free(str2), NULL);
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
	return (unified);
}
