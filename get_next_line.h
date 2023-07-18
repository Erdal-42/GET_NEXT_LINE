/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:39:55 by ekocak            #+#    #+#             */
/*   Updated: 2023/07/18 14:05:59 by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETNEXTLINE_H
# define GETNEXTLINE_H

#include <stdlib.h>
#include <unistd.h>

char	*read_line(int, char *);
char	*ft_strjoin(char *, char *);
int		ft_strlen(char *);
char	*get_line(char *);
char	*ft_truncate(char *);
int     present_nl(char *);
void    print_message(char *);
char    *get_next_line(int);
#endif