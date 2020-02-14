/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:57:06 by xtang             #+#    #+#             */
/*   Updated: 2019/11/26 16:28:00 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Param. #1: The content in stack memory.
** Param. #2: If has the "reading" line. store the line into point line.
** Return value: can be 0 - no "reading" line in stack memory.
**                      1 - has "reading"line in stack mempry,
**							store the "reading" line into pointer of line.
**                          remove "reading" line from stack memory.
*/

static int	gnl_verify_line(char **stack, char **line, int fd)
{
	char	*tmp_stack;
	char	**strchr_stack;
	size_t	i;
	size_t	len;

	i = 0;
	strchr_stack = stack;
	len = ft_strlen(strchr_stack[fd]);
	while (strchr_stack[fd][i] != '\0')
	{
		if (strchr_stack[fd][i] == '\n')
		{
			if (i == (len - 1))
				tmp_stack = NULL;
			else
				tmp_stack = ft_strdup(&strchr_stack[fd][i + 1]);
			*line = ft_strsub(&strchr_stack[fd][0], 0, i);
			free(strchr_stack[fd]);
			stack[fd] = tmp_stack;
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** Param. #1: The file descriptor.
** Param. #2: The heap memeory stores reading contents from file.
** Param. #3: It is a static variable. Saving contents from heap and dealing.
** Param. #4: The address of a pointer to be a charactor that will be used to
**             save the line read from the file descriptor.
** Return value: can be  1 - when ret biger than 1, the return of read() is
**                            ret. continue to read;
**						 0 - Don't read contents, stop to read;
**					    -1 - Reading error.
*/

static int	gnl_read_file(int fd, char *heap, char **stack, char **line)
{
	size_t	ret;
	char	*temp_stack;

	while ((ret = read(fd, heap, BUFF_SIZE)) > 0)
	{
		heap[ret] = '\0';
		if (stack[fd])
		{
			temp_stack = stack[fd];
			stack[fd] = ft_strjoin(temp_stack, heap);
			free(temp_stack);
			temp_stack = NULL;
		}
		else
			stack[fd] = ft_strdup(heap);
		if (gnl_verify_line(stack, line, fd))
			break ;
	}
	if (ret > 0)
		return (1);
	else
		return (ret);
}

/*
** Param. #1: The file descriptor that will be used to read.
** Param. #2: The address of a pointer to be a charactor that will be used to
**            save the line read from the file descriptor.
** Return Value: can be  1  - a line has been read;
**                       0  - when the reading has been completed;
**                      -1  - an error has happened.
*/

int			get_next_line(const int fd, char **line)
{
	size_t		result;
	static char	*stack[MAX_FD];
	char		*heap;

	if ((!line) || (fd < 0 || fd > MAX_FD) || (read(fd, stack[fd], 0) < 0))
		return (-1);
	if (!(heap = (char *)malloc(BUFF_SIZE + 1)))
		return (-1);
	if (stack[fd])
		if (gnl_verify_line(stack, line, fd))
		{
			free(heap);
			return (1);
		}
	result = gnl_read_file(fd, heap, stack, line);
	free(heap);
	if (result != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!result && *line)
			*line = NULL;
		return (result);
	}
	*line = stack[fd];
	stack[fd] = NULL;
	return (1);
}
