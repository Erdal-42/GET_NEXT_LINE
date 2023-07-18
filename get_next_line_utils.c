/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elraira- <elraira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 10:43:18 by elraira-          #+#    #+#             */
/*   Updated: 2021/09/05 14:17:37 by elraira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	c;

	c = 0;
	if (!str)
		return (0);
	while (str[c] != '\0')
		c++;
	return (c);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
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
	{
		unified[i ++] = *(str2 ++);
	}
	unified[i] = '\0';
	free(str1);
	return (unified);
}
