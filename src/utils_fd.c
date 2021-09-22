/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:12:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/22 21:29:09 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_open_file(char *file_name, int flags, int mod)
{
	int		fd;
	char	*err_message;

	if (mod)
		fd = open(file_name, flags, mod);
	else
		fd = open(file_name, flags);
	if (fd == ERROR)
	{
		err_message = strerror(errno);
		ft_putstr_fd("pipex: ", 2, NONE);
		ft_putstr_fd(err_message, 2, NONE);
		ft_putstr_fd(": ", 2, NONE);
		ft_putstr_fd(file_name, 2, NEWLINE);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	ft_get_fd(t_env *env, char *argv[])
{
	int	fd;
	int	open_flags;

	fd = 0;
	open_flags = ft_get_open_flags(env);
	if (env->heredoc && env->pos == FIRST_CMD_WHEN_HEREDOC)
	{
		fd = ft_open_file("heredoc_output", O_RDONLY, 0);
		if (dup2(fd, 0) == ERROR)
			ft_exit_with_error_message(env, "dup2 failed");
	}
	else if (env->pos == FIRST_CMD)
	{
		fd = ft_open_file(argv[INPUT_FILE], O_RDONLY, 0);
		if (dup2(fd, 0) == ERROR)
			ft_exit_with_error_message(env, "dup2 failed");
	}
	else if (env->pos == env->argc - GET_LAST_CMD)
	{
		fd = ft_open_file(argv[env->argc - 1], open_flags, 0664);
		if (dup2(fd, 1) == ERROR)
			ft_exit_with_error_message(env, "dup2 failed");
	}
	return (fd);
}

void	ft_putstr_fd(char *s, int fd, bool option)
{
	if (s)
	{
		write(fd, s, ft_strlen(s));
		if (option == NEWLINE)
			write(fd, "\n", 1);
	}
}
