/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/06 15:15:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_exit_when_error_occurs(char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}

void	ft_call_child_to_execute_cmd(int *pipe_fds, char **argv)
{
	int		fd;
	char	**cmd1;

	close(0);
	close(1);
	if (dup2(pipe_fds[1], 1) == -1)
		ft_exit_when_error_occurs("dup2");
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	cmd1 = ft_split(argv[2], ' ');
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit_when_error_occurs("open");
	if (execvp(cmd1[0], cmd1) == -1)
		ft_exit_when_error_occurs("execvp");
	close(fd);
}

void	ft_call_parent_to_execute_cmd(int *pipe_fds, char **argv)
{
	int 	file_fd;
	char	**cmd2;

	close(0);
	close(1);
	if (dup2(pipe_fds[0], 0) == -1)
		ft_exit_when_error_occurs("dup2");
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	cmd2 = ft_split(argv[3], ' ');
	file_fd = open(argv[4], O_CREAT | O_WRONLY);
	dup2(1, file_fd);
//	error = execve(cmd2[0], cmd2, NULL);
	if (execvp(cmd2[0], cmd2) == -1)
		ft_exit_when_error_occurs("execvp");
	close(file_fd);
	wait(NULL);
}

int main(int argc, char *argv[])
{
	int     pipe_fds[2];
	pid_t   pid;

    if(argc < 5)
    {
        printf("Usage: ./pipex <input file> <cmd1> <cmd2> <output file>\n");
        exit(EXIT_FAILURE);
    }
	if (pipe(pipe_fds) == -1)
		ft_exit_when_error_occurs("pipe");
	pid = fork();
	if (pid == -1)
		ft_exit_when_error_occurs("fork");
	if (pid == 0)
		ft_call_child_to_execute_cmd(pipe_fds, argv);
	else
		ft_call_parent_to_execute_cmd(pipe_fds, argv);
	exit(EXIT_SUCCESS);
}
