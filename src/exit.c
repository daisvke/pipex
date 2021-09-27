/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 23:18:50 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/27 05:50:43 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_free_pipe_fds(t_env *env)
{
	int	size;
	int	i;

	size = env->cmd_nbr;
	i = 0;
	while (i < size)
	{
		free(env->pipe_fds[i]);
		++i;
	}
	if (size > 0)
		free(env->pipe_fds);
}

char	**ft_get_array_of_error_messages(char *errors[])
{
	errors[0] = "\nUsage1: ./pipex [input file] [cmd1] [cmd2] [output file]\n" \
		"Usage2: ./pipex here_doc [limiter] [cmd] [cmd1] [output file]\n";
	errors[1] = "malloc failed";
	errors[2] = "failed to fork child process";
	errors[3] = "pipe failed";
	errors[4] = "dup2 failed";
	errors[5] = "close failed";
	errors[6] = "get_next_line failed";
	errors[7] = "split failed";
	errors[8] = "permission denied:";
	return (errors);
}

char	*ft_get_err_message_from_err_code(int err_code)
{
	char	*err_messages[ERR_MAX + 1];

	ft_get_array_of_error_messages(err_messages);
	return (err_messages[err_code]);
}

void	ft_exit_with_error_message(t_env *env, int err_code)
{
	char	*err_message;

	err_message = NULL;
	err_message = ft_get_err_message_from_err_code(err_code);
	ft_putstr_fd("\npipex: ", STDERR_FILENO, NONE);
	ft_putstr_fd(err_message, STDERR_FILENO, NEWLINE);
	if (err_code != 0)
		ft_free_pipe_fds(env);
	exit(EXIT_FAILURE);
}

void	ft_exit_when_cmd_not_found(t_env *env, char *cmd)
{
	ft_putstr_fd("pipex: command not found: ", STDERR_FILENO, NONE);
	ft_putstr_fd(cmd, STDERR_FILENO, NEWLINE);
	ft_free_array_of_pointers(env->cmd, 0);
	ft_free_pipe_fds(env);
	exit(EXIT_FAILURE);
}
