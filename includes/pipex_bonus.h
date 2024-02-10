/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:24:58 by yboutsli          #+#    #+#             */
/*   Updated: 2024/02/10 22:22:10 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include "ft_printf.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strtrim(char const *s1);
char	**execv_argv(char *arg, char **npath);
char	*cmd_path(char **cmd, char **npath);
void	ft_free(char **tab);
char	**path(char **envp);
int		file1(char *file);
int		file2(char *file, int hd);
int		exist_file(char *file);
char	*get_next_line(int fd);
void	middle_process(char *cmd, char **npath);
void	middle_execution(int fd[2], char *cmd, char **npath);
void	child_process1(char *cmd, char **npath);
void	child_process2(char *cmd, char **npath);
void	close2(int tab[2]);
#endif