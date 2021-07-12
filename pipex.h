/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/12 13:58:19 by dtanigaw         ###   ########.fr       */
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

# define OK						1
# define FIRST_CMD				2
# define GET_LAST_CMD			2
# define INPUT_FILE				1
# define NO_INPUT_FILE			0
# define FIRST_CMD_WHEN_HEREDOC 3

/*
** get_next_line
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# define ERROR -1
# define ERROR2 -2
# define REACHED_EOF 0
# define LINE_READ 1

typedef struct s_env
{
	int		pipe_fds[2];
	int		pos;
	int		argc;
	int		fd_in;
	bool	heredoc;
}			t_env;

/*
** utils_fd
*/
int		ft_get_fd(t_env *env, char *argv[]);
void	ft_input_heredoc(t_env *env, char *argv[]);

/*
** path
*/
bool	ft_check_access(char *path);
char	*ft_get_key_value_from_envp(char *envp[], char *key);
char	*ft_get_the_right_cmd_path(t_env *env, char *envp[], char *key, char *cmd);

/*
** exit
*/
void	ft_exit_and_print_usage(void);
void	ft_exit_when_cmd_not_found(t_env *env, char *cmd);
void	ft_exit_when_error_occurs(t_env *env, char *error_message);
void	ft_exit_with_error_message(t_env *env, char *error_message);
void	ft_free_path_to_cmd(char *path_to_cmd);

/*
** utils_str
*/
void	ft_free_array_of_pointers(char **array_of_pointers, size_t arr_size);
void	ft_free_split(char **array_of_pointers);
char	*ft_join_three_str(t_env *env, char *str1, char *str2, char *str3);

int		get_next_line(int fd, char **line);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr(char *str);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*
** get_next_line
*/
int		ft_gnl_bzero(char *s, size_t n);
int		ft_gnl_strchr(char *s, char c);
size_t	ft_gnl_strlen(char *s);
char	*ft_gnl_substr(char *s, size_t start, size_t len);
char	*ft_strdup(char *src, int size);

#endif
