/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/22 04:13:34 by dtanigaw         ###   ########.fr       */
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

/*
** get_next_line
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 			32
# endif

# define NOT_FOUND				0
# define OFF					-1
# define REACHED_EOF 			0
# define LINE_READ				1

typedef struct s_gnl
{
	int				fd;
	char			*content;
	char			buffer[BUFFER_SIZE + 1];
	struct s_gnl	*next;
}					t_gnl;	
/*
** end get_next_line
*/

typedef struct s_env
{
	int		pipe_fds[2];
	int		pos;
	int		argc;
	int		fd_in;
	bool	heredoc;
}			t_env;

void	ft_close(t_env *env, int fd);
void	ft_dup2(t_env *env, int fd1, int fd2);
pid_t	ft_fork(t_env *env);
void	*ft_malloc(t_env *env, size_t num, size_t size);
void	ft_pipe(t_env *env, int *fds);
/*
** utils_fd
*/
int		ft_get_fd(t_env *env, char *argv[]);
int		ft_open_file(char *file_name, int flags, int mod);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);

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
void	ft_exit_and_print_usage(void);
void	ft_exit_when_cmd_not_found(t_env *env, char *cmd);
void	ft_exit_when_error_occurs(t_env *env, char *error_message);
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

/*
** get_next_line
*/
int		get_next_line(int fd, char **line);
int		ft_gnl_bzero(char *s, size_t n);
int		ft_gnl_strchr(char *s, char c);
size_t	ft_gnl_strlen(char *s);
char	*ft_gnl_substr(char *s, size_t start, size_t len);
char	*ft_strdup(char *src, int size);

#endif
