/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/06 05:01:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_exit_when_error_occurs(char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int     pipe_fds[2];
	int		fd;
	pid_t   childpid;
	char    readbuffer[30];
	int		error;

	char	**cmd1;
	char	**cmd2;
    if(argc < 3)
    {
        printf("Usage: ./Step1 <exclusions file> <folder1> <folder2> <folder3> ...\n");
        return -1;
    }
	if (pipe(pipe_fds) == -1)
		ft_exit_when_error_occurs("pipe");
	childpid = fork();
	if (childpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (childpid == 0)
	{
		close(0);
		close(1);
		dup2(pipe_fds[1], 1);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		cmd1 = ft_split(argv[2], ' ');
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			ft_exit_when_error_occurs("open");
		error = execvp(cmd1[0], cmd1);
		if (error == -1)
			ft_exit_when_error_occurs("execvp");
		close(fd);
		//	if (error == EACCESS)
		//		printf("[ERROR] Permission is denied for a file\n");
	}
	else
	{
		close(0);
		dup2(pipe_fds[0], 0);
		close(pipe_fds[1]);
		cmd2 = ft_split(argv[3], ' ');
		error = execvp(cmd2[0], cmd2);
//		error = execve(cmd2[0], cmd2, NULL);
		if (error == -1)
			ft_exit_when_error_occurs("execvp");
	//	while (read(
		wait(NULL);
	}
	exit(EXIT_SUCCESS);
}
