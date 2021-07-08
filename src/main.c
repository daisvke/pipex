/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/08 17:28:09 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_exit_when_error_occurs(char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}

bool	ft_check_access(char *path)
{
	if (access(path, F_OK) != 0 || access(path, X_OK) != 0)
		return (false);
	return (true);
}

char	*ft_get_key_value_from_envp(char *envp[], char *key)
{
	size_t	i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0)
			return (envp[i] + key_len);
		++i;
	}
	return (NULL);
}

char	*ft_get_the_right_cmd_path(char *envp[], char *key, char *cmd)
{
	char	*paths_envp;
	char	**paths_envp_split;
	char	*path_cmd_at_i;
	size_t	i;

	paths_envp = ft_get_key_value_from_envp(envp, "PATH=");
//	if path_envp == NULL 
	paths_envp_split = ft_split(paths_envp, ':');
	i = 0;
	path_cmd_at_i = NULL;

	while (paths_envp_split[i])
	{
		path_cmd_at_i = ft_join_three_str(paths_envp_split[i], "/", cmd);
		if (ft_check_access(path_cmd_at_i) == OK)
			break ;
		free(path_cmd_at_i);
		++i;
	}
	ft_free_split(paths_envp_split);
	if (!path_cmd_at_i)
	{
		free(paths_envp);
	}
	return (path_cmd_at_i);
}

void	ft_call_child_to_execute_cmd(int *pipe_fds, char *argv[])
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

void	ft_call_parent_to_execute_cmd(int *pipe_fds, char *argv[], char *envp[])
{
	int 	file_fd;
	char	*path_to_cmd;
	char	**cmd2;

	wait(NULL);
	cmd2 = ft_split(argv[3], ' ');
	close(0);
	close(1);
	if (dup2(pipe_fds[0], 0) == -1)
		ft_exit_when_error_occurs("dup2");
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	file_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	dup2(1, file_fd);
	path_to_cmd = ft_get_the_right_cmd_path(envp, "PATH=", cmd2[0]);
	if (execve(path_to_cmd, cmd2, NULL) == -1)
	{
		free(path_to_cmd);
		ft_exit_when_error_occurs("execve");
	}
	free(path_to_cmd);
	path_to_cmd = NULL;
	close(file_fd);
}

int main(int argc, char *argv[], char *envp[])
{
	int     pipe_fds[2];
	pid_t   pid;

    if(argc < 5)
    {
		// in stderr
        ft_putstr("Usage: ./pipex <input file> <cmd1> <cmd2> <output file>\n");
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
		ft_call_parent_to_execute_cmd(pipe_fds, argv, envp);
	exit(EXIT_SUCCESS);
}
