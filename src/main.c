/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/12 13:00:03 by dtanigaw         ###   ########.fr       */
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

int	ft_get_fd(t_env *env, char *argv[])
{
	int	fd;

	fd = 0;
 	if (env->heredoc && env->pos == FIRST_CMD_WHEN_HEREDOC)
	{
		fd = ft_open_file("heredoc_output", O_RDONLY, 0);
		if (dup2(fd, 0) == -1)
			ft_exit_with_error_message("dup2 failed");
	}
	else if (env->pos == FIRST_CMD)
	{
		fd = ft_open_file(argv[INPUT_FILE], O_RDONLY, 0);
		if (dup2(fd, 0) == -1)
			ft_exit_with_error_message("dup2 failed");
	}
	else if (env->pos == env->argc - GET_LAST_CMD)
	{
		fd = ft_open_file(argv[env->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);		
		if (dup2(fd, 1) == -1)
			ft_exit_with_error_message("dup2 failed");
	}
	return (fd);
}

void	ft_input_heredoc(char *argv[])
{
	int		fd;
	char	*line;

	line = NULL;
	fd = ft_open_file("heredoc_output", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (dup2(fd, 1) == -1)
		ft_exit_with_error_message("dup2 failed");
	while (get_next_line(0, &line))
	{
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
			break ;
		ft_putstr_fd(line, 1);
		ft_putstr_fd("\n", 1);
		free(line);
	}
	free(line);
	line = NULL;
	close(fd);
}

void	ft_spawn_child_to_execute_cmd(t_env *env, char *argv[], char *envp[])
{
	char	*path_to_cmd;
	char	**cmd1;
	int		fd;

	close(1);
	if (dup2(env->pipe_fds[1], 1) == -1)
		ft_exit_with_error_message("dup2 failed");
	if (dup2(env->fd_in, 0) == -1)
		ft_exit_with_error_message("dup2 failed");
	close(env->pipe_fds[0]);
	close(env->pipe_fds[1]);
	cmd1 = ft_split(argv[env->pos], ' ');
	fd = ft_get_fd(env, argv);
	path_to_cmd = ft_get_the_right_cmd_path(envp, "PATH=", cmd1[0]);
	if (path_to_cmd && execve(path_to_cmd, cmd1, envp) == -1)
		ft_exit_when_cmd_not_found(cmd1[0]);
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

	env->pos += 2;
	if (env->heredoc)
		ft_input_heredoc(argv);
	while (env->pos < env->argc - 1)
	{
		if (pipe(env->pipe_fds) == -1)
				ft_exit_with_error_message("pipe failed");
		pid = fork();
		if (pid == -1)
			ft_exit_with_error_message("failed to fork child process");
		if (pid == 0)
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
	env->pipe_fds[0] = 0;
	env->pipe_fds[1] = 0;
	env->pos = 0;
	env->argc = 0;
	env->fd_in = 0;
	env->argc = argc;
	env->heredoc = false;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
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
