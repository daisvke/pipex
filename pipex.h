/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 02:26:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/09 02:12:46 by dtanigaw         ###   ########.fr       */
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

# define OK	1

/*
** path
*/
bool	ft_check_access(char *path);
char	*ft_get_key_value_from_envp(char *envp[], char *key);
char	*ft_get_the_right_cmd_path(char *envp[], char *key, char *cmd);

/*
** exit
*/
void	ft_exit_when_cmd_not_found(char *cmd);
void	ft_exit_when_error_occurs(char *error_message);
void	ft_exit_with_error_message(char *error_message);

/*
** utils_str
*/
void	ft_free_array_of_pointers(char **array_of_pointers, size_t arr_size);
void	ft_free_split(char **array_of_pointers);
char	*ft_join_three_str(char *str1, char *str2, char *str3);


int		get_next_line(int fd, char **line);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr(char *str);
void	ft_putstr_fd(char *s, int fd);
char    **ft_split(char const *s, char c); 
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
