/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaure <mfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:47:44 by mfaure            #+#    #+#             */
/*   Updated: 2025/07/10 17:38:40 by mfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
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
	if (str[limb] == '\n')
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
	keeper = malloc(sizeof(char) * (strlen - limb) + 1);
	i = 0;
	while (str[limb + i] != '\0')
	{
		keeper[i] = str[limb + i];
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
	char *temp2;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	size = 1;
	// str = "";
	str = malloc(1);
	str[0] = '\0';
	buffer = malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (keeper) {
		temp2 = ft_strjoin(str, keeper);
		free(str);
		str = temp2;
		free(keeper);
	}
	count = ft_strlen(str);
	size = read(fd, buffer, BUFFER_SIZE);
	if (size == -1) {
		free(buffer);
		free(str);
		return NULL;
	}
	while (size > 0)
	{
		buffer[size] = '\0';
		count += size;
		char *temp = ft_strjoin(str, buffer);
		// printf("count %i\n", count);
		free(str);
		str = temp;
		if (find_in_str(str) == -1)
			break ;
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == -1) {
			free(buffer);
			free(str);
			return NULL;
		}
	}
	// while (find_in_str(str) > 0 && size != 0)
	// {
	// 	size = read(fd, buffer, BUFFER_SIZE);
	// 	// if (size == 0 && keeper[0] == '\0')
	// 	// 	return NULL;
	// 	count += size;
	// 	buffer[size] = '\0';
	// 	char *temp = ft_strjoin(str, buffer);
	// 	printf("count %i\n", count);
	// 	free(str);
	// 	str = temp;
	// }
	free(buffer);
	// str[count] = '\0';
	if (size == 0 && str[0] == '\0') {
			free(str);
			return NULL;
	}
	keeper = amputate_str(str);
	str[find_limb(str)] = '\0';
	// if (size == 0 && str[0] == '\0') {
	// 		free(buffer);
	// 		free(str);
	// 		return NULL;
	// }
	return (str);
}

int	main(int ac, char **av)
{
	int	fd;

	if (ac == 1)
		return (0);
	fd = open(av[1], S_IRUSR);
	
	char *test = get_next_line(fd);
	printf("%s\n", test);
	free(test);
	// test = get_next_line(fd);
	// printf("%s\n", test);
	// free(test);
	
	// printf("%s\n", get_next_line(fd)); 
	//char *test = get_next_line(fd);
	//while (test)
	//{
	//	printf("'%s'", test);
	//	free(test);
	//	test = get_next_line(fd);
	//}
	//return (0);
}

	// printf("%i\n", strlen - limb);
// if (keeper == NULL)
// 		strdup("");