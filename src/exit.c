/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 23:18:50 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/12 13:52:37 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// FREE T_ENV
void	ft_exit_and_print_usage(void)
{
	ft_putstr_fd(\
		"Usage: ./pipex [input file] [cmd1] [cmd2] [output file]\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_exit_with_error_message(t_env *env, char *error_message)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putendl_fd(error_message, 2);
	if (env)
		free(env);
	env = NULL;
	exit(EXIT_FAILURE);
}

void	ft_exit_when_cmd_not_found(t_env *env, char *cmd)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	if (env)
		free(env);
	env = NULL;
	exit(EXIT_FAILURE);
}

void	ft_free_path_to_cmd(char *path_to_cmd)
{
	if (path_to_cmd)
	{
		free(path_to_cmd);
		path_to_cmd = NULL;
	}
}
