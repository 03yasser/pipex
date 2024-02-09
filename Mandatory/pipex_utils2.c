/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:36:49 by yboutsli          #+#    #+#             */
/*   Updated: 2024/02/09 17:09:40 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close2(int tab[2])
{
	close(tab[0]);
	close(tab[1]);
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

int	file2(char *file)
{
	int	fd;

	if (!exist_file(file))
		fd = open (file, O_CREAT | O_WRONLY, 0644);
	else if (access(file, W_OK) == -1)
	{
		perror(file);
		return (-1);
	}
	else
		fd = open (file, O_WRONLY | O_TRUNC);
	return (fd);
}
