/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 03:34:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/27 05:48:47 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_get_open_flags(t_env *env)
{
	int	flags;

	flags = 0;
	if (env->heredoc && env->pos == env->argc - GET_LAST_CMD)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else if (env->pos == env->argc - GET_LAST_CMD)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	return (flags);
}

void	ft_input_heredoc(t_env *env, char *argv[])
{
	int		fd;
	char	*line;
	char	*limiter;

	line = NULL;
	limiter = argv[2];
	fd = ft_open_file(env, "heredoc_output", \
		O_CREAT | O_WRONLY | O_TRUNC, 0664);
	ft_dup2(env, fd, 1);
	while (get_next_line(0, &line) >= 0)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == SAME)
		{
			free(line);
			line = NULL;
			ft_close(env, fd);
			return ;
		}
		ft_putstr_fd(line, 1, NONE);
		ft_putstr_fd("\n", 1, NONE);
		free(line);
	}
	line = NULL;
	ft_close(env, fd);
	ft_exit_with_error_message(env, 6);
}
