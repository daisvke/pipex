/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 01:34:45 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/09 01:57:25 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

bool	ft_check_access(char *path)
{
	if (access(path, F_OK) != 0 || access(path, X_OK) != 0)
		return (false);
	return (true);
}

char	*ft_get_key_value_from_envp(char *envp[], char *key)
{
	size_t	i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0)
			return (envp[i] + key_len);
		++i;
	}
	return (NULL);
}

char	*ft_get_the_right_cmd_path(char *envp[], char *key, char *cmd)
{
	char	*paths_envp;
	char	**paths_envp_split;
	char	*path_cmd_at_i;
	size_t	i;

	paths_envp = ft_get_key_value_from_envp(envp, key);
	paths_envp_split = ft_split(paths_envp, ':');
	i = 0;
	path_cmd_at_i = NULL;
	while (paths_envp_split[i])
	{
		path_cmd_at_i = ft_join_three_str(paths_envp_split[i], "/", cmd);
		if (ft_check_access(path_cmd_at_i) == OK)
			break ;
		free(path_cmd_at_i);
		++i;
	}
	ft_free_split(paths_envp_split);
	paths_envp_split = NULL;
	return (path_cmd_at_i);
}

