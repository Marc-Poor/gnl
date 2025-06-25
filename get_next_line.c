/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaure <mfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:47:44 by mfaure            #+#    #+#             */
/*   Updated: 2025/06/25 19:11:39 by mfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int find_in_str(char *buffer)
{
	int i = 0;

	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
	i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	char	*str;
	char	*buffer;
	int		size;

	size = 0;
	buffer = "";
	while (find_in_str(buffer) < 0)
		size += read(fd, buffer, 10);
	str = ft_strjoin(str, buffer);
	return (str);
}

int main(int ac, char **av)
{
	if (ac == 1)
		return 0;
	int fd = open(av[1], S_IRUSR);
	printf("%s\n", get_next_line(fd));
	return 0;
}