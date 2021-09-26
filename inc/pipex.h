/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/26 05:30:06 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>

# include "get_next_line.h"

# define STDERR					2
# define NEWLINE				1
# define NONE					0
# define OK						1
# define FIRST_CMD				2
# define GET_FIRST_CMD			2
# define GET_LAST_CMD			2
# define INPUT_FILE				1
# define NO_INPUT_FILE			0
# define FIRST_CMD_WHEN_HEREDOC 3
# define ERROR 					-1
# define SUCCESS				0
# define CHILD					0
# define SAME					0
# define DIFFERENT				1

typedef struct s_env
{
	int		**pipe_fds;
	int		pos;
	int		cmd_nbr;
	int		i;
	int		argc;
	int		fd_in;
	char	**cmd;
	bool	heredoc;
}			t_env;

void	ft_close_and_free_pipe_fds(t_env *env);
int		ft_pipex(char *argv[], char *envp[], t_env *env);

/*
** system calls
*/
void	ft_close(t_env *env, int fd);
void	ft_dup2(t_env *env, int fd1, int fd2);
pid_t	ft_fork(t_env *env);
void	*ft_malloc(t_env *env, size_t num, size_t size);
void	ft_pipe(t_env *env, int *fds);

/*
** utils_fd
*/
int		ft_get_fd(t_env *env, char *argv[]);
int		ft_open_file(t_env *env, char *file_name, int flags, int mod);
void	ft_putstr_fd(char *s, int fd, bool option);

/*
** path
*/
bool	ft_check_access(char *path);
char	*ft_get_key_value_from_envp(char *envp[], char *key);
char	*ft_get_the_right_cmd_path(t_env *env, char *envp[], char *key, \
	char *cmd);

/*
** exit
*/
void	ft_exit_and_print_usage(t_env *env);
void	ft_exit_failure(t_env *env);
void	ft_exit_when_cmd_not_found(t_env *env, char *cmd, char *path_to_cmd);
void	ft_exit_with_error_message(t_env *env, char *error_message);
void	ft_free_path_to_cmd(char *path_to_cmd);

/*
** utils_str
*/
void	ft_free_array_of_pointers(char **array_of_pointers, size_t arr_size);
char	*ft_join_three_str(t_env *env, char *str1, char *str2, char *str3);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);

/*
** split
*/
void	ft_free_split(char **array_of_pointers);
char	**ft_split(char const *s, char c);

/*
** heredoc
*/
int		ft_get_open_flags(t_env *env);
void	ft_input_heredoc(t_env *env, char *argv[]);

#endif
