/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaure <mfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:48:18 by mfaure            #+#    #+#             */
/*   Updated: 2025/07/04 16:08:55 by mfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*fill_up_str(int size1, char const *s1, char *str)
{
	int	i;

	i = 0;
	while (i < size1)
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		size1;
	int		size2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	str = malloc(sizeof(char) * ((size1 + size2) + 1));
	if (!str)
		return (NULL);
	str = fill_up_str(size1, s1, str);
	i = 0;
	while (i < size2)
	{
		str[i + size1] = s2[i];
		i++;
	}
	str[(size1 + size2)] = '\0';
	return (str);
}
