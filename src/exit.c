/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 23:18:50 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/09 00:43:08 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_exit_with_error_message(char *error_message)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putendl_fd(error_message, 2);
	exit(EXIT_FAILURE);
}
/*
void	ft_exit_when_error_occurs(char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}
*/
void	ft_exit_when_cmd_not_found(char *cmd)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	exit(EXIT_FAILURE);
}
