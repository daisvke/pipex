/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/10 01:52:36 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_open_file(char *file_name, int flags, int mod)
{
	int		fd;
	char	*err_message;

	if (mod)
		fd = open(file_name, flags, mod);
	else
		fd = open(file_name, flags);
	if (fd == -1)
	{
		err_message = strerror(errno);
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(err_message, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(file_name, 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
/*
void	ft_spawn_child_to_execute_cmd(int *pipe_fds, char *argv[], int pos, \
	char *envp[])
{
	char	*path_to_cmd;
	char	**cmd;

	close(0);
	close(1);
	if (dup2(pipe_fds[0], 0) == -1)
		ft_exit_with_error_message("dup2 failed");
	if (dup2(pipe_fds[1], 1) == -1)
		ft_exit_with_error_message("dup2 failed");
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	cmd = ft_split(argv[pos], ' ');
	path_to_cmd = ft_get_the_right_cmd_path(envp, "PATH=", cmd[0]);
	if (path_to_cmd && execve(path_to_cmd, cmd, envp) == -1)
		ft_exit_when_cmd_not_found(cmd[0]);
	if (path_to_cmd)
	{
		free(path_to_cmd);
		path_to_cmd = NULL;
	}
}*/

void	ft_spawn_child_to_execute_cmd(int fd_in, int *pipe_fds, int argc, char *argv[], \
	int pos, char *envp[])
{
	char	*path_to_cmd;
	char	**cmd1;
	int		fd;

	if (dup2(pipe_fds[1], 1) == -1)
		ft_exit_with_error_message("dup2 failed");
	if (dup2(fd_in, 0) == -1)
		ft_exit_with_error_message("dup2 failed");
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	cmd1 = ft_split(argv[pos], ' ');
	if (pos == 2)
	{
		fd = ft_open_file(argv[1], O_RDONLY, 0);
		if (dup2(fd, 0) == -1)
			ft_exit_with_error_message("dup2 failed for fd");
	}
	if (pos == argc - 2)
	{
		fd = ft_open_file(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (dup2(fd, 1) == -1)
			ft_exit_with_error_message("dup2 failed");
	}
	path_to_cmd = ft_get_the_right_cmd_path(envp, "PATH=", cmd1[0]);
	if (path_to_cmd && execve(path_to_cmd, cmd1, envp) == -1)
		ft_exit_when_cmd_not_found(cmd1[0]);
	if (path_to_cmd)
	{
		free(path_to_cmd);
		path_to_cmd = NULL;
	}
	close(fd);
}
/*
void	ft_call_parent_to_execute_cmd(int *pipe_fds, int argc, char *argv[], \
	char *envp[])
{
	int		fd;
	char	*path_to_cmd;
	char	**cmd2;

	cmd2 = ft_split(argv[argc - 2], ' ');
	close(0);
	close(1);
	if (dup2(pipe_fds[0], 0) == -1)
		ft_exit_with_error_message("dup2 failed");
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	fd = ft_open_file(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (dup2(1, fd) == -1)
		ft_exit_with_error_message("dup2 failed");
	path_to_cmd = ft_get_the_right_cmd_path(envp, "PATH=", cmd2[0]);
	if (execve(path_to_cmd, cmd2, NULL) == -1)
		ft_exit_when_cmd_not_found(cmd2[0]);
	if (path_to_cmd)
	{
		free(path_to_cmd);
		path_to_cmd = NULL;
	}
	close(fd);
}*/

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fds[2];
	int		fd_in = 0;
	int		i;
	pid_t	pid;

	if (argc < 5)
	{
		ft_putstr_fd(\
			"Usage: ./pipex [input file] [cmd1] [cmd2] [output file]\n", 2);
		exit(EXIT_FAILURE);
	}
	i = 2;
	while (i < argc - 1)
	{
		if (pipe(pipe_fds) == -1)
			ft_exit_with_error_message("pipe failed");
		pid = fork();
		if (pid == -1)
			ft_exit_with_error_message("failed to fork child process");
		if (pid == 0)
			ft_spawn_child_to_execute_cmd(fd_in, pipe_fds, argc, argv, i, envp);
		else
		{
			close(1);
			close(pipe_fds[1]);
			fd_in = pipe_fds[0];	
			close(pipe_fds[1]);
			++i;
		}
	}
	exit(EXIT_SUCCESS);
}
