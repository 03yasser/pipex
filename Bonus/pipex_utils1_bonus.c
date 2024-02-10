/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:51:51 by yboutsli          #+#    #+#             */
/*   Updated: 2024/02/10 22:13:38 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;

	if ((int) count < 0 && (int) size < 0)
		return (NULL);
	if ((size && count > (4294967295 / size)))
		return (NULL);
	p = malloc (count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

char	*ft_strtrim(char const *s1)
{
	char	*p;
	int		i;
	int		len;
	int		x;

	x = 0;
	if (ft_strlen(s1) == 0 || s1[0] != '/')
		return (NULL);
	i = -1;
	while (s1[++i])
		if (s1[i] == '/')
			x = i;
	len = ft_strlen(s1) - x;
	if (len <= 0 || x == 0)
		return (NULL);
	p = malloc (len * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[++x])
		p[i++] = s1[x];
	p[len - 1] = '\0';
	return (p);
}

int	file1(char *file)
{
	int	fd;

	if (!exist_file(file) || access(file, R_OK) == -1)
	{
		perror(file);
		return (-1);
	}
	fd = open (file, O_RDONLY);
	return (fd);
}

int	file2(char *file, int hd)
{
	int	fd;

	if (!exist_file(file))
		fd = open (file, O_CREAT | O_WRONLY, 0644);
	else if (access(file, W_OK) == -1)
	{
		perror(file);
		return (-1);
	}
	else if (hd == 1)
		fd = open (file, O_APPEND | O_WRONLY);
	else
		fd = open (file, O_WRONLY | O_TRUNC);
	return (fd);
}
