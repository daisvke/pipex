/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:29:43 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/08 17:27:07 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_join_three_str(char *str1, char *str2, char *str3)
{
	char	*joined;
	size_t	joined_len;
	size_t	str1_len;
	size_t	str2_len;
	size_t	str3_len;

	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	str3_len = ft_strlen(str3);
	joined_len = str1_len + str2_len + str3_len;
	joined = malloc(joined_len * sizeof(*joined));
	if (!joined)
		ft_exit_when_error_occurs("join_str");
	ft_memcpy(joined, str1, str1_len);
	ft_memcpy(&joined[str1_len], str2, str2_len);
	ft_memcpy(&joined[str1_len + str2_len], str3, str3_len);
	joined[joined_len] = '\0';
	return (joined);
}

void	ft_free_split(char *split[])
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		++i;
	}
	free(split);
	split = NULL;
}
