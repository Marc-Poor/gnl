/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaure <mfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:47:44 by mfaure            #+#    #+#             */
/*   Updated: 2025/07/19 16:03:53 by mfaure           ###   ########.fr       */
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
	char		*temp;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	size = 1;
	str = ft_strdup("");
	buffer = malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (keeper)
	{
		temp = ft_strjoin(str, keeper);
		free(str);
		str = temp;
		free(keeper);
	}
	size = read(fd, buffer, BUFFER_SIZE);
	if (size == -1)
		return (free(buffer), free(str), NULL);
	while (size > 0)
	{
		buffer[size] = '\0';
		char	*temp2 = ft_strjoin(str, buffer);
		free(str);
		str = temp2;
		if (find_in_str(str) == -1)
			break ;
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == -1)
			return (free(buffer), free(str), NULL);
	}
	free(buffer);
	if (size == 0 && str[0] == '\0')
		return (free(str), NULL);
	keeper = amputate_str(str);
	str[find_limb(str)] = '\0';
	return (str);
}

//#include <fcntl.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
//
//extern char *get_next_line(int fd);
//extern int next_read_error;
//
//void test_gnl(int fd, char *expected) {
//    char *line = get_next_line(fd);
//    printf("Expected: %s", expected ? expected : "NULL\n");
//    printf("Got     : %s", line ? line : "NULL\n");
//
//    if ((expected == NULL && line == NULL) || (line && expected && strcmp(line, expected) == 0)) {
//        printf("Result  : OK\n");
//    } else {
//        printf("Result  : KO\n");
//    }
//
//    free(line);
//}

//
//int main(void) {
//	int next_read_error = 0;
//    int fd = open("read_error.txt", O_RDONLY);
//    if (fd < 0) {
//        perror("open");
//        return 1;
//    }
//
//    // Simulate a read error
// 	/* 1 */ test_gnl(fd, "aaaaaaaaaa\n");
//	/* 2 */ test_gnl(fd, "bbbbbbbbbb\n");
//	// set the next read call to return -1
//	next_read_error = 1;
//	if (BUFFER_SIZE > 100) {
//		char *temp;
//		do {
//			temp = get_next_line(fd);
//			free(temp);
//		} while (temp != NULL);
//	}
//	/* 3 */ test_gnl(fd, NULL);
//    // Reset error and close file
//    next_read_error = 0;
//	close(fd);
//	fd = open("read_error.txt", O_RDONLY);
//	/* 4 */ test_gnl(fd, "aaaaaaaaaa\n");
//	/* 5 */ test_gnl(fd, "bbbbbbbbbb\n");
//	/* 6 */ test_gnl(fd, "cccccccccc\n");
//	/* 7 */ test_gnl(fd, "dddddddddd\n");
//	/* 8 */ test_gnl(fd, NULL);
//    close(fd);
//    return 0;
//}