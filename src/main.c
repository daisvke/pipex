/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/03 12:16:44 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(int argc, char *argv[])
{
	int     pipe_fds[2];
	int		gnl_fd;
	char	*gnl_line;
	pid_t   childpid;
	char    *string;
	char    readbuffer[30];

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
		close(pipe_fds[0]);
		gnl_fd = open(argv[1], O_RDONLY);
		get_next_line(gnl_fd, &gnl_line);
		string = "Hello, world!\0";
		write(pipe_fds[1], gnl_line, strlen(gnl_line) + 1);
	}
	else
	{
	//	wait(NULL);
		close(pipe_fds[1]);
		read(pipe_fds[0], readbuffer, sizeof(readbuffer));
		printf("Read text is: %s\n", readbuffer);
	}
	return(0);
}
