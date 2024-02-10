/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:04:32 by yboutsli          #+#    #+#             */
/*   Updated: 2024/02/10 22:15:03 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	child_process1(char *cmd, char **npath)
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
	if (execv(execv_args[0], execv_args) == -1)
		perror(execv_args[0]);
}

void	middle_execution(int fd[2], char *cmd, char **npath)
{
	char	**execv_args;

	dup2(fd[1], 1);
	close2(fd);
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
	if (execv(execv_args[0], execv_args) == -1)
		perror(execv_args[0]);
}

void	middle_process(char *cmd, char **npath)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit (EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Fork: ");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		middle_execution(fd, cmd, npath);
	dup2(fd[0], 0);
	close2(fd);
}
