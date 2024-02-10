/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:02:18 by yboutsli          #+#    #+#             */
/*   Updated: 2024/02/10 22:33:47 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strtrim(char *s1);
char	**execv_argv(char *arg, char **npath);
void	close2(int tab[2]);
char	**path(char **envp);
int		file2(char *file);
int		file1(char *file);
void	ft_free(char **tab);
int		exist_file(char *file);

#endif