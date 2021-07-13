/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/13 03:52:13 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_spawn_child_to_execute_cmd(t_env *env, char *argv[], char *envp[])
{
	char	*path_to_cmd;
	char	**cmd1;
	int		fd;

	close(1);
	if (dup2(env->pipe_fds[1], 1) == ERROR)
		ft_exit_with_error_message(env, "dup2 failed");
	if (dup2(env->fd_in, 0) == ERROR)
		ft_exit_with_error_message(env, "dup2 failed");
	close(env->pipe_fds[0]);
	close(env->pipe_fds[1]);
	cmd1 = ft_split(argv[env->pos], ' ');
	fd = ft_get_fd(env, argv);
	path_to_cmd = ft_get_the_right_cmd_path(env, envp, "PATH=", cmd1[0]);
	if (path_to_cmd && execve(path_to_cmd, cmd1, envp) == ERROR)
		ft_exit_when_cmd_not_found(env, cmd1[0]);
	ft_free_path_to_cmd(path_to_cmd);
	close(fd);
}

void	ft_save_data_from_child(t_env *env)
{
	close(env->pipe_fds[1]);
	env->fd_in = env->pipe_fds[0];
	++env->pos;
}

void	ft_pipex(char *argv[], char *envp[], t_env *env)
{
	pid_t	pid;

	env->pos += GET_FIRST_CMD;
	if (env->heredoc)
		ft_input_heredoc(env, argv);
	while (env->pos < env->argc - 1)
	{
		if (pipe(env->pipe_fds) == ERROR)
			ft_exit_with_error_message(env, "pipe failed");
		pid = fork();
		if (pid == ERROR)
			ft_exit_with_error_message(env, "failed to fork child process");
		if (pid == SUCCESS)
			ft_spawn_child_to_execute_cmd(env, argv, envp);
		else
			ft_save_data_from_child(env);
	}
	if (env->heredoc)
		unlink("heredoc_output");
}

t_env	*ft_init_env(int argc, char *argv[])
{
	t_env	*env;

	env = malloc(sizeof(*env));
	if (!env)
		ft_exit_with_error_message(env, "malloc failed");
	env->pipe_fds[0] = 0;
	env->pipe_fds[1] = 0;
	env->pos = 0;
	env->argc = 0;
	env->fd_in = 0;
	env->argc = argc;
	env->heredoc = false;
	if (ft_strncmp(argv[1], "here_doc", 8) == SAME)
	{
		env->heredoc = true;
		++env->pos;
	}
	return (env);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env;

	if (argc < 5)
		ft_exit_and_print_usage();
	env = NULL;
	env = ft_init_env(argc, argv);
	ft_pipex(argv, envp, env);
	free(env);
	env = NULL;
	exit(EXIT_SUCCESS);
}
