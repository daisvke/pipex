/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 04:39:25 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/24 16:29:50 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_spawn_child_to_execute_cmd(t_env *env, char *argv[], char *envp[])
{
	char	*path_to_cmd;
	int		fd;

	ft_dup2(env, env->fd_in, 0);
	ft_close(env, env->fd_in);
	ft_dup2(env, env->pipe_fds[env->i][1], 1);
	ft_close(env, env->pipe_fds[env->i][1]);
	fd = ft_get_fd(env, argv);
	env->cmd = ft_split(argv[env->pos], ' ');
	if (!env->cmd)
		ft_exit_with_error_message(env, "split failed");
	path_to_cmd = ft_get_the_right_cmd_path(env, envp, "PATH=", env->cmd[0]);
	if (path_to_cmd && execve(path_to_cmd, env->cmd, envp) == ERROR)
		ft_exit_when_cmd_not_found(env, env->cmd[0]);
	ft_free_array_of_pointers(env->cmd, 0);
	ft_free_path_to_cmd(path_to_cmd);
	ft_close(env, fd);
}

void	ft_save_data_from_child(t_env *env)
{
	ft_close(env, env->pipe_fds[env->i][1]);
	env->fd_in = env->pipe_fds[env->i][0];
	++env->pos;
	++env->i;
}

void	ft_wait_for_all_children(t_env *env)
{
	int	i;
	int	size;

	i = 0;
	size = env->cmd_nbr;
	while (i < size)
	{
		wait(NULL);
		++i;
	}
}

void	ft_pipex(char *argv[], char *envp[], t_env *env)
{
	pid_t	pid;

	env->pos += GET_FIRST_CMD;
	if (env->heredoc)
		ft_input_heredoc(env, argv);
	while (env->pos < env->argc - 1)
	{
		ft_pipe(env, env->pipe_fds[env->i]);
		pid = ft_fork(env);
		if (pid == CHILD)
		{
			ft_spawn_child_to_execute_cmd(env, argv, envp);
			return ;
		}
		ft_save_data_from_child(env);
	}
	ft_wait_for_all_children(env);
	if (env->heredoc)
		unlink("heredoc_output");
	ft_close_and_free_pipe_fds(env);
}
