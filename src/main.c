/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/26 20:57:54 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_init_pipe_fds(t_env *env)
{
	int	size;
	int	i;

	size = env->cmd_nbr;
	env->pipe_fds = malloc(sizeof(int *) * size);
	i = 0;
	while (i < size)
	{
		env->pipe_fds[i] = malloc(sizeof(int) * 2);
		env->pipe_fds[i][0] = 0;
		env->pipe_fds[i][1] = 0;
		++i;
	}
}

void	ft_init_env(int argc, char *argv[], t_env *env)
{
	env->pos = 0;
	env->i = 0;
	env->argc = 0;
	env->fd_in = 0;
	env->argc = argc;
	env->cmd = NULL;
	env->heredoc = false;
	if (ft_strncmp(argv[1], "here_doc", 8) == SAME)
	{
		env->heredoc = true;
		++env->pos;
	}
	env->cmd_nbr = env->argc - 3 - env->pos;
	ft_init_pipe_fds(env);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	env;
	int		res;

	envp = NULL;
	if (argc < 5)
		ft_exit_and_print_usage(&env);
	ft_init_env(argc, argv, &env);
	res = ft_pipex(argv, envp, &env);
	exit(res);
}
