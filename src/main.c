/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/04 10:26:57 by root             ###   ########.fr       */
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

	char	**cmd;

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
		dup2(pipe_fds[1], 1);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		gnl_fd = open(argv[1], O_RDONLY);
		get_next_line(gnl_fd, &gnl_line);
		write(1, gnl_line, strlen(gnl_line) + 1);
	 }
	else
	{
	//	wait(NULL);
		cmd = ft_split(argv[2], ' ');
		dup2(pipe_fds[0], 0);
		close(pipe_fds[1]);
		close(pipe_fds[0]);
		read(0, readbuffer, sizeof(readbuffer));

		if (execvp(cmd[0], cmd) == -1)
		{
			if (error == EACCESS)
				printf("[ERROR] Permission is denied for a file\n");
			else
				perror("execvp");
			exit(EXIT_FAILURE);
		}
		printf("Read text is: %s\n", readbuffer);
	}
	exit(EXIT_SUCCESS);
}