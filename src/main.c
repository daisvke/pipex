/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/09 03:33:53 by dtanigaw         ###   ########.fr       */
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

void	ft_call_child_to_execute_cmd(int *pipe_fds, char *argv[], char *envp[])
{
	char	*path_to_cmd;
	char	**cmd1;
	int		fd;

	close(0);
	close(1);
	if (dup2(pipe_fds[1], 1) == -1)
		ft_exit_with_error_message("dup2 failed");
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	cmd1 = ft_split(argv[2], ' ');
	fd = ft_open_file(argv[1], O_RDONLY, 0);
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

void	ft_call_parent_to_execute_cmd(int *pipe_fds, char *argv[], char *envp[])
{
	int		fd;
	char	*path_to_cmd;
	char	**cmd2;

	cmd2 = ft_split(argv[3], ' ');
	close(0);
	close(1);
	if (dup2(pipe_fds[0], 0) == -1)
		ft_exit_with_error_message("dup2 failed");
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	fd = ft_open_file(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0664);
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
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fds[2];
	pid_t	pid;

	if (argc < 5)
	{
		ft_putstr_fd(\
			"Usage: ./pipex [input file] [cmd1] [cmd2] [output file]\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_fds) == -1)
		ft_exit_with_error_message("pipe failed");
	pid = fork();
	if (pid == -1)
		ft_exit_with_error_message("failed to fork child process");
	if (pid == 0)
		ft_call_child_to_execute_cmd(pipe_fds, argv, envp);
	else
		ft_call_parent_to_execute_cmd(pipe_fds, argv, envp);
	exit(EXIT_SUCCESS);
}
