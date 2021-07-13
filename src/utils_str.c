/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:29:43 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/13 03:58:57 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_free_array_of_pointers(char **array_of_pointers, size_t arr_size)
{
	size_t	pointer;

	pointer = 0;
	while (pointer < arr_size)
	{
		free(array_of_pointers[pointer]);
		++pointer;
	}
	free(array_of_pointers);
	array_of_pointers = NULL;
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (!dest && !src)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
}

char	*ft_join_three_str(t_env *env, char *str1, char *str2, char *str3)
{
	char	*joined;
	size_t	joined_len;
	size_t	str1_len;
	size_t	str2_len;
	size_t	str3_len;

	if (!str1 || !str2 || !str3)
		ft_exit_with_error_message(env, "permission denied:");
	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	str3_len = ft_strlen(str3);
	joined_len = str1_len + str2_len + str3_len;
	joined = malloc((joined_len + 1) * sizeof(*joined));
	if (!joined)
		ft_exit_with_error_message(env, "join_three_str failed");
	ft_memcpy(joined, str1, str1_len);
	ft_memcpy(&joined[str1_len], str2, str2_len);
	ft_memcpy(&joined[str1_len + str2_len], str3, str3_len);
	joined[joined_len] = '\0';
	return (joined);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (s1 && s2)
	{
		while ((*s1 || *s2) && n--)
		{
			if (*s1 != *s2)
				return ((unsigned char)(*s1) - (unsigned char)(*s2));
			s1++;
			s2++;
		}
		return (SAME);
	}
	return (DIFFERENT);
}
