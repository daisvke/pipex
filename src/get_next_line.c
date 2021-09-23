/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 04:07:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/23 04:28:06 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

size_t	gnl_get_char_index(char *str, char c, bool increment)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	if (increment)
		return (i);
	else
		return (NOT_FOUND);
}

char	*gnl_concatenate(char *s1, char *s2, int len, bool is_empty)
{
	char	*str;
	size_t	i;
	size_t	size;

	size = 0;
	if (s1 && is_empty == false)
		size += gnl_get_char_index(s1, '\0', true);
	if (s2)
		size += gnl_get_char_index(s2, '\0', true);
	if (len >= 0 && (int)size > len)
		size = len;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (is_empty == false && s1 && *s1 && i < size)
		str[i++] = *s1++;
	while (s2 && *s2 && i < size)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

int	gnl_get_line(char **data, int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			ret;
	char		*tmp;

	while (gnl_get_char_index(*data, '\n', false) == NOT_FOUND)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
			return (ERROR);
		if (ret == 0)
			break ;
		buffer[ret] = '\0';
		tmp = gnl_concatenate(*data, buffer, OFF, false);
		if (!tmp)
			return (ERROR);
		free(*data);
		*data = tmp;
	}
	return (ret);
}

int	gnl_run_and_return(char **data, char **line, int fd)
{
	int			ret;
	size_t		index;
	char		*tmp;
	bool		is_empty;

	ret = gnl_get_line(data, fd);
	if (ret == ERROR)
		return (ERROR);
	index = 0;
	if (*data)
		index = gnl_get_char_index(*data, '\n', true);
	is_empty = index + 1 > gnl_get_char_index(*data, '\0', true);
	*line = gnl_concatenate(*data, NULL, index, false);
	if (!line)
		return (ERROR);
	tmp = gnl_concatenate(*data + index + 1, NULL, \
		gnl_get_char_index(*data, '\0', true) - index - 1, is_empty);
	if (!tmp)
		return (ERROR);
	free(*data);
	*data = tmp;
	if (ret == REACHED_EOF && is_empty)
		return (REACHED_EOF);
	else
		return (LINE_READ);
}

int	get_next_line(int fd, char **line)
{
	static char	*data;

	if (BUFFER_SIZE <= 0 || !line)
		return (ERROR);
	return (gnl_run_and_return(&data, line, fd));
}
