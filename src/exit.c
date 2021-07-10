/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 23:18:50 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/10 02:19:13 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_exit_and_print_usage(void)
{
	ft_putstr_fd(\
		"Usage: ./pipex [input file] [cmd1] [cmd2] [output file]\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_exit_with_error_message(char *error_message)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putendl_fd(error_message, 2);
	exit(EXIT_FAILURE);
}

void	ft_exit_when_cmd_not_found(char *cmd)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
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
