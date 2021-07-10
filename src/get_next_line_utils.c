/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:30:20 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/10 04:37:56 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_gnl_bzero(char *s, size_t n)
{
	if (!s)
		return (0);
	while (*s && n--)
		*s++ = '\0';
	return (1);
}

int	ft_gnl_strchr(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

char	*ft_gnl_substr(char *s, size_t start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	size;

	size = 0;
	i = start;
	while (s[i++] && len--)
		size++;
	p = ft_strdup((char *)&s[start], size);
	if (!p)
		return (NULL);
	return (p);
}
