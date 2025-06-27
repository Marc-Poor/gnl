/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaure <mfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:47:44 by mfaure            #+#    #+#             */
/*   Updated: 2025/06/27 18:34:24 by mfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int find_in_str(char *str, int size)
{
	int i = 0;

	while (i < size)
	{
		if (str[i] == '\n' || str[i] == '\0'){
			return (-1);
			}
		i++;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char	*str;
	char	*buffer;
	static char *keeper;
	int		size;

	size = 0;
	str = "";
	printf("keeper : %s\n", keeper);
	while (find_in_str(str, size) > 0) {
		size += read(fd, buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = '\0';
		str = ft_strjoin(str, buffer);
	}
	keeper = "keep";
	return (str);
}

int main(int ac, char **av)
{
	if (ac == 1)
		return 0;
	int fd = open(av[1], S_IRUSR);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return 0;
}