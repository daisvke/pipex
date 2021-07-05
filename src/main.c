/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/05 14:42:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(int argc, char *argv[])
{
	int     pipe_fds[2];
	int		gnl_fd;
	char	*gnl_line;
	pid_t   childpid;
	char    readbuffer[30];
	int	error;

	char	**cmd1;
	char	**cmd2;

	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	childpid = fork();
	if (childpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (childpid == 0)
	{
		cmd2 = ft_split(argv[3], ' ');
		dup2(pipe_fds[1], 1);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		error = execvp(cmd2[0], cmd2);
		if (execvp(cmd2[0], cmd2) == -1)
		{
				perror("execvp");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	//	gnl_fd = open(argv[1], O_RDONLY);
	//	get_next_line(gnl_fd, &gnl_line);
	//	write(1, gnl_line, strlen(gnl_line) + 1);
	 }
	else
	{
	//	wait(NULL);
		cmd1 = ft_split(argv[2], ' ');
		dup2(pipe_fds[0], 0);
//		close(pipe_fds[1]);
//		close(pipe_fds[0]);
	//	read(0, readbuffer, sizeof(readbuffer));
		error = execvp(cmd1[0], cmd1);
		if (execvp(cmd1[0], cmd1) == -1)
		{
		//	if (error == EACCESS)
		//		printf("[ERROR] Permission is denied for a file\n");
		//	else
				perror("execvp");
			exit(EXIT_FAILURE);
		}
//		printf("Read text is: %s\n", readbuffer);
	}
	exit(EXIT_SUCCESS);
}
