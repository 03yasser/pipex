/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:51:51 by yboutsli          #+#    #+#             */
/*   Updated: 2024/02/03 14:02:49 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
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

char	*ft_strdup(const char *s1)
{
	size_t	len_s;
	size_t	i;
	char	*p;

	i = 0;
	len_s = ft_strlen(s1);
	p = (char *) malloc (sizeof(char) * (len_s + 1));
	if (!s1 || !p) 
		return (NULL);
	while (i < len_s)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;

	if ((int) count < 0 && (int) size <  0)
        return (NULL);
	if ((size && count > (4294967295 / size)))
		return (NULL);
	p = malloc (count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
    if (!s)
        return (0);
	while (s[i])
		i++;
	return (i);
}
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	p = ft_calloc(len + 1, sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	return (p);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*p;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen (s2);
	p = (char *)malloc (sizeof(char) * (len_s1 + len_s2 + 1));
	if (!p)
		return (NULL);
	while (i < len_s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (j < len_s2 && s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[j + i] = '\0';
	return (p);
}
static int	exist(char const c, char const *set)
{
	size_t	j;

	j = 0;
	while (set[j])
	{
		if (c == set[j])
			return (1);
		j++;
	}
	return (0);
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
