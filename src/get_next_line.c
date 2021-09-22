/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 04:07:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/22 04:08:37 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	gnl_get_char_pos(char *str, char c, bool increment)
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
		size += gnl_get_char_pos(s1, '\0', true);
	if (s2)
		size += gnl_get_char_pos(s2, '\0', true);
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

int	gnl_fill_line(t_gnl *fd_data, int fd)
{
	int		ret;
	char	*tmp;

	while (gnl_get_char_pos(fd_data->content, '\n', false) == NOT_FOUND)
	{
		ret = read(fd, fd_data->buffer, BUFFER_SIZE);
		if (ret < 0)
			return (ERROR);
		if (ret == 0)
			break ;
		fd_data->buffer[ret] = '\0';
		tmp = gnl_concatenate(fd_data->content, fd_data->buffer, OFF, false);
		if (!tmp)
			return (ERROR);
		free(fd_data->content);
		fd_data->content = tmp;
	}
	return (ret);
}

int	gnl_execute_and_return(t_gnl *fd_data, char **line, int fd)
{
	int		ret;
	size_t	pos;
	char	*tmp;
	bool	is_empty;

	ret = gnl_fill_line(fd_data, fd);
	if (ret == ERROR)
		return (ERROR);
	pos = 0;
	if (fd_data->content)
		pos = gnl_get_char_pos(fd_data->content, '\n', true);
	is_empty = pos + 1 > gnl_get_char_pos(fd_data->content, '\0', true);
	*line = gnl_concatenate(fd_data->content, NULL, pos, false);
	if (!line)
		return (ERROR);
	tmp = gnl_concatenate(fd_data->content + pos + 1, NULL, \
		gnl_get_char_pos(fd_data->content, '\0', true) - pos - 1, is_empty);
	if (!tmp)
		return (ERROR);
	free(fd_data->content);
	fd_data->content = tmp;
	if (ret == REACHED_EOF && is_empty)
		return (REACHED_EOF);
	else
		return (LINE_READ);
}

int	get_next_line(int fd, char **line)
{
	static t_gnl	*data;
	t_gnl			*fd_data;

	if (BUFFER_SIZE <= 0 || !line)
		return (ERROR);
	fd_data = data;
	while (fd_data && fd_data->fd != fd)
		fd_data = fd_data->next;
	if (!fd_data)
	{
		fd_data = malloc(sizeof(t_gnl));
		if (!fd_data)
			return (ERROR);
		fd_data->fd = fd;
		fd_data->content = NULL;
		fd_data->next = data;
		data = fd_data;
	}
	return (gnl_execute_and_return(fd_data, line, fd));
}
