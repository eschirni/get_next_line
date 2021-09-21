/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 20:45:18 by eschirni          #+#    #+#             */
/*   Updated: 2021/09/07 14:35:13 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_delall(char **a)
{
	free(*a);
	*a = NULL;
	return (NULL);
}

static char	*ft_append(char *start, char *end)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	tmp = malloc(ft_strclen(start, '\0') + ft_strclen(end, '\0') + 1);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (start[i] != '\0')
	{
		tmp[i] = start[i];
		i++;
	}
	j = 0;
	while (end[j] != '\0')
	{
		tmp[i] = end[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	free(start);
	return (tmp);
}

static void	ft_reading(char **rest, int fd)
{
	char	*buffer;
	int		val;

	buffer = ft_calloc(BUFFER_SIZE + 1);
	val = read(fd, buffer, BUFFER_SIZE);
	while (val > 0)
	{
		buffer[val] = '\0';
		if (*rest == NULL)
			*rest = ft_strcdup(buffer, '\0', 0);
		else
			*rest = ft_append(*rest, buffer);
		if (ft_strchr(*rest, '\n') != NULL)
			break ;
		val = read(fd, buffer, BUFFER_SIZE);
	}
	if (val < 0)
		ft_delall(rest);
	ft_delall(&buffer);
}

char	*get_next_line(int fd)
{
	static char	*rest[10240];
	char		*temp;
	char		*ret;

	if (fd < 0)
		return (NULL);
	ft_reading(&rest[fd], fd);
	if (rest[fd] == NULL || rest[fd][0] == '\0')
		return (NULL);
	else if (ft_strchr(rest[fd], '\n') != NULL)
	{
		ret = ft_strcdup(rest[fd], '\n', 0);
		temp = ft_strcdup(rest[fd], '\0', ft_strclen(rest[fd], '\n') + 1);
		free(rest[fd]);
		rest[fd] = temp;
		if (rest[fd][0] == '\0')
			ft_delall(&rest[fd]);
	}
	else
	{
		ret = ft_strcdup(rest[fd], '\0', 0);
		ft_delall(&rest[fd]);
	}
	return (ret);
}
// #include <stdio.h>
// # include <fcntl.h>
// int main()
// {
//     int     fd;
// 	int     fd2;
//     fd = open("abc.txt", O_RDONLY);
// 	fd2 = open("abc copy.txt", O_RDONLY);
//     printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("\n\n\n");
// 	printf("%s", get_next_line(fd2));
// 	printf("%s", get_next_line(fd2));
// 	printf("%s", get_next_line(fd2));
// 	printf("\n\n\n");
// 	printf("%s", get_next_line(fd));
// 	printf("\n\n\n");
// 	printf("%s", get_next_line(fd2));
// 	printf("%s", get_next_line(fd2));
//     close(fd);
// 	close(fd2);
// }