/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 01:34:45 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/27 05:17:27 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

bool	ft_check_access(char *path)
{
	if (access(path, F_OK) != SUCCESS || access(path, X_OK) != SUCCESS)
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
		if (ft_strncmp(envp[i], key, key_len) == SAME)
			return (envp[i] + key_len);
		++i;
	}
	return (NULL);
}

static char	**ft_get_path(char *envp[], t_env *env, char *key)
{
	char	*paths_envp;
	char	**paths_envp_split;

	paths_envp = ft_get_key_value_from_envp(envp, key);
	paths_envp_split = ft_split(paths_envp, ':');
	if (!paths_envp_split)
		ft_exit_with_error_message(env, 7);
	return (paths_envp_split);
}

char	*ft_get_the_right_cmd_path(t_env *env, char *envp[], \
	char *key, char *cmd)
{
	char	**paths_envp_split;
	char	*cmd_path_at_i;
	size_t	i;

	if (ft_check_access(cmd) == OK)
		return (cmd);
	paths_envp_split = ft_get_path(envp, env, key);
	i = 0;
	cmd_path_at_i = NULL;
	while (paths_envp_split[i])
	{
		cmd_path_at_i = ft_join_three_str(env, paths_envp_split[i], "/", cmd);
		if (ft_check_access(cmd_path_at_i) == OK)
			break ;
		free(cmd_path_at_i);
		cmd_path_at_i = NULL;
		++i;
	}
	if (cmd_path_at_i == NULL)
		cmd_path_at_i = cmd;
	ft_free_split(paths_envp_split);
	paths_envp_split = NULL;
	return (cmd_path_at_i);
}
