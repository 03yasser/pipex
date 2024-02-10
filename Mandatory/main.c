/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:05:51 by yboutsli          #+#    #+#             */
/*   Updated: 2024/02/10 22:17:31 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

void	child_process1(int fd[2], int file[2], char *cmd, char **npath)
{
	char	**execv_args;

	if (cmd[0] == '\0')
	{
		ft_printf(2, "permission denied:\n");
		return ;
	}
	execv_args = execv_argv(cmd, npath);
	if (!execv_args[0])
	{
		ft_printf(2, "command not found: %s\n", cmd);
		exit (EXIT_FAILURE);
	}
	dup2(file[0], 0);
	dup2(fd[1], 1);
	close2(file);
	close2(fd);
	if (execv(execv_args[0], execv_args) == -1)
		perror(execv_args[0]);
}

void	child_process2(int fd[2], int file[2], char *cmd, char **npath)
{
	char	**execv_args;

	if (!cmd[0])
	{
		ft_printf(2, "permission denied\n");
		return ;
	}
	execv_args = execv_argv(cmd, npath);
	if (!*execv_args)
	{
		ft_printf(2, "command not found: %s\n", cmd);
		exit(EXIT_FAILURE);
	}
	dup2(file[1], 1);
	dup2(fd[0], 0);
	close2(file);
	close2(fd);
	if (execv(execv_args[0], execv_args) == -1)
		perror(execv_args[0]);
}

void	process(int fd[2], int file[2], char **argv, char **npath)
{
	int	pid[2];

	pid[0] = fork();
	if (pid[0] < 0)
	{
		perror("Fork: ");
		exit(EXIT_FAILURE);
	}
	if (pid[0] == 0)
		child_process1(fd, file, argv[2], npath);
	pid[1] = fork();
	if (pid[1] < 0)
	{
		perror("Fork: ");
		exit(EXIT_FAILURE);
	}
	if (pid[1] == 0)
		child_process2(fd, file, argv[3], npath);
	close2(fd);
	close2(file);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}

void	pipex(char **argv, char **npath)
{
	int	fd[2];
	int	file[2];

	file[0] = file1(argv[1]);
	file[1] = file2(argv[4]);
	if (file[0] < 0 || file[1] < 0)
		return ;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit (EXIT_FAILURE);
	}
	process(fd, file, argv, npath);
}

int	main(int argc, char **argv, char *envp[])
{
	char	**npath;

	if (argc != 5)
		return (1);
	npath = path(envp);
	pipex(argv, npath);
	ft_free(npath);
	return (0);
}
