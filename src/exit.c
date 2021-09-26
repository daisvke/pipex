/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 23:18:50 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/26 05:59:11 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_close_and_free_pipe_fds(t_env *env)
{
	int	size;
	int	i;

//	size = env->i;
	size = env->cmd_nbr;
	i = 0;
	while (i < size)
	{
//		if (env->pipe_fds[i][0])
		ft_close(env, env->pipe_fds[i][0]);
//		if (env->pipe_fds[i][1])
//			ft_close(env, env->pipe_fds[i][1]);
		free(env->pipe_fds[i]);
		++i;
	}
	free(env->pipe_fds);
}

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
	free(env->pipe_fds);
}

void	ft_exit_failure(t_env *env)
{
	ft_free_pipe_fds(env);
	(void)env;
	exit(EXIT_FAILURE);
}

void	ft_exit_and_print_usage(t_env *env)
{
	ft_putstr_fd(\
		"Usage1: ./pipex [input file] [cmd1] [cmd2] [output file]\n" \
		"Usage2: ./pipex here_doc [limiter] [cmd] [cmd1] [output file]\n", \
		STDERR_FILENO, NONE);
	//ft_exit_failure(env);
	(void)env;
	exit(EXIT_FAILURE);
}

void	ft_exit_with_error_message(t_env *env, char *error_message)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO, NONE);
	ft_putstr_fd(error_message, STDERR_FILENO, NEWLINE);
	ft_exit_failure(env);
}

void	ft_exit_when_cmd_not_found(t_env *env, char *cmd)
{
	ft_putstr_fd("pipex: command not found: ", STDERR_FILENO, NONE);
	ft_putstr_fd(cmd, STDERR_FILENO, NEWLINE);
	ft_free_array_of_pointers(env->cmd, 0);
//	ft_free_path_to_cmd(path_to_cmd);
	ft_exit_failure(env);
}

void	ft_free_path_to_cmd(char *path_to_cmd)
{
	if (path_to_cmd)
	{
		free(path_to_cmd);
		path_to_cmd = NULL;
	}
}
