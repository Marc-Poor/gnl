/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaure <mfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:47:44 by mfaure            #+#    #+#             */
/*   Updated: 2025/07/04 18:48:06 by mfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int	find_in_str(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (-1);
		i++;
	}
	return (1);
}

int	find_limb(char *str)
{
	int	limb;

	limb = 0;
	while (str[limb] != '\n' && str[limb] != '\0')
		limb++;
	return (limb);
}

char	*amputate_str(char *str)
{
	int		strlen;
	int		limb;
	char	*keeper;
	int		i;

	strlen = ft_strlen(str);
	limb = find_limb(str);
	if (limb == strlen)
		return (NULL);
	keeper = malloc(sizeof(char) * (strlen - limb));
	i = 0;
	while (str[limb + i] != '\0')
	{
		keeper[i] = str[limb + i + 1];
		i++;
	}
	keeper[i] = '\0';
	return (keeper);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		*buffer;
	static char	*keeper;
	int			size;
	int			count;

	size = 1;
	str = "";
	buffer = NULL;
	str = ft_strjoin(str, keeper);
	if (str == NULL)
		str = "";
	count = ft_strlen(str);
	while (find_in_str(str) > 0 && size != 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		count += size;
		if (size == 0)
			break ;
		buffer[BUFFER_SIZE] = '\0';
		str = ft_strjoin(str, buffer);
	}
	str[count] = '\0';
	keeper = amputate_str(str);
	str[find_limb(str)] = '\0';
	return (str);
}

int	main(int ac, char **av)
{
	int	fd;

	if (ac == 1)
		return (0);
	fd = open(av[1], S_IRUSR);
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	return (0);
}

	// printf("%i\n", strlen - limb);