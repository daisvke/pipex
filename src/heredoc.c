/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 03:34:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/13 03:52:13 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

	line = NULL;
	fd = ft_open_file("heredoc_output", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (dup2(fd, 1) == ERROR)
		ft_exit_with_error_message(env, "dup2 failed");
	while (get_next_line(0, &line))
	{
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == SAME)
			break ;
		ft_putstr_fd(line, 1);
		ft_putstr_fd("\n", 1);
		free(line);
	}
	free(line);
	line = NULL;
	close(fd);
}
