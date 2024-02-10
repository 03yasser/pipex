/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:16:10 by yboutsli          #+#    #+#             */
/*   Updated: 2024/02/10 22:16:45 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close2(int tab[2])
{
	close(tab[0]);
	close(tab[1]);
}

void	here_doc(char *LIMITER)
{
	char	*str;
	int		fd;

	fd = open("/tmp/here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		exit(EXIT_FAILURE);
	str = get_next_line(0);
	while (ft_strncmp(str, LIMITER, ft_strlen(LIMITER)) != 0)
	{
		ft_printf(fd, str);
		free(str);
		str = get_next_line(0);
	}
	free(str);
	close(fd);
}

void	pipex_utils(int hd, int argc, char **argv, char **npath)
{
	int	i;
	int	file;

	if (hd == 1)
		i = 3;
	else
		i = 2;
	while (i < argc - 2)
		middle_process(argv[i++], npath);
	file = file2(argv[argc - 1], hd);
	dup2(file, 1);
	close(file);
	child_process2(argv[argc - 2], npath);
}

void	pipex(int argc, char **argv, char **npath)
{
	int		file[2];
	int		hd;

	hd = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		hd = 1;
		here_doc(argv[2]);
		file[0] = file1("/tmp/here_doc");
	}
	else
	{
		file[0] = file1(argv[1]);
		file[1] = file2(argv[argc - 1], hd);
	}
	if (file[0] < 0 || file[1] < 0)
		exit (EXIT_FAILURE);
	dup2(file[0], 0);
	close2(file);
	pipex_utils(hd, argc, argv, npath);
}

int	main(int argc, char **argv, char *envp[])
{
	char	**npath;

	if (argc < 5)
		exit(EXIT_FAILURE);
	npath = path(envp);
	pipex(argc, argv, npath);
	ft_free(npath);
	exit(EXIT_SUCCESS);
}
