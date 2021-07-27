/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 22:37:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/27 23:15:58 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_close(t_env *env, int fd)
{
	if (close(fd) == ERROR)
		ft_exit_with_error_message(env, "close failed");
}

void	ft_dup2(t_env *env, int fd1, int fd2)
{
	if (dup2(fd1, fd2) == ERROR)
		ft_exit_with_error_message(env, "dup2 failed");
}

void	ft_pipe(t_env *env, int *fds)
{
	if (pipe(fds) == ERROR)
		ft_exit_with_error_message(env, "pipe failed");
}

pid_t	ft_fork(t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == ERROR)
		ft_exit_with_error_message(env, "failed to fork child process");
	return (pid);
}

void	*ft_malloc(t_env *env, size_t num, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(num * size);
	if (!ptr)
		ft_exit_with_error_message(env, "malloc failed");
	return (ptr);
}
		
