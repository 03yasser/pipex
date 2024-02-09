/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:02:08 by yboutsli          #+#    #+#             */
/*   Updated: 2024/02/03 12:05:47yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>



int	exist_file(char *file)
{
	if (access(file, F_OK) == -1)
		return (0);
	else
		return (1);	
}

int	file1 (char *file)
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

int	file2 (char *file)
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

char	**path(char **envp)
{
	int		i;
	int		j;
	char	*path;
	char	**npath;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			npath = ft_split(path, ':');
			free (path);
			j = 0;
			return (npath);
		}
		i++;
	}
	return (NULL);
}
char	*cmd_path(char **cmd, char **npath)
{
	int		i;
	char	*tmp;
	char	*tmp1;

	if (**cmd == '\0')
		return (NULL);
	if (*cmd[0] == '/')
		return (*cmd);
	i = 0;
	while (npath[i])
	{
		tmp = ft_strjoin(npath[i], "/");
		tmp1 = ft_strjoin(tmp, *cmd);
		free(tmp);
		if (!access(tmp1, F_OK))
			return (tmp1);
		free(tmp1);
		i++;
	}
	return (NULL);
}
void ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}
void check()
{
	system("leaks pipex");
}
void	child_process2(char *f2, char *cmd, char **npath)
{
	char	**execv_args;
	int	fd2;
	int	pid;

	if (!cmd[0])
	{
		write(2, "permission denied\n", 18);
		exit(EXIT_FAILURE);
	}
	fd2 = file2(f2);
	dup2(fd2, 1);
	close(fd2);
	execv_args = execv_argv(cmd, npath);
	pid = fork();
	if (pid == 0)
		execv(execv_args[0], execv_args);
}
void	middle_procees(char *cmd, char **npath)
{
	char	**execv_args;
	int	fd[2];
	int	pid;

	if (!cmd[0])
	{
		write(2, "permission denied\n", 18);
		exit(EXIT_FAILURE);
	}
	pipe(fd);
	dup2(fd[1], 1);
	close(fd[1]);
	execv_args = execv_argv(cmd, npath);
	pid = fork();
	if (pid == 0)
		execv(execv_args[0], execv_args);
	dup2(fd[0], 0);
}
void child_process1(char *f1, char *cmd, char **npath)
{
	char	**execv_args;
	int		fd1;
	int		fd[2];
	int		pid;

	fd1 = file1(f1);
	pipe(fd);
	dup2(fd1, 0);
	close(fd1);
	dup2(fd[1], 1);
	close(fd[1]);
	if (!cmd[0])
	{
		write(2, "permission denied\n", 18);
		exit(EXIT_FAILURE);
	}
	execv_args = execv_argv(cmd, npath);
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
    }
	if (pid == 0)
	{
		if (execv(execv_args[0], execv_args) == -1)
			perror(execv_args[0]);
	}
	dup2(fd[0], 0);
	close(fd[0]);
}
void	pipex(int argc, char **argv, char **npath)
{
	int	tmp;
	int	pid;
	int	fd1;
	int	i;

	child_process1(argv[1], argv[2], npath);
	i = 3;
	while (i < argc - 1)
		middle_procees(argv[i++], npath);
	child_process2(argv[argc - 1], argv[argc - 2], npath);
	while (waitpid(0, 0, 0) != -1)
		;
}

char	**execv_argv(char *arg, char **npath)
{
	char	*cmd;
	char	*ccmd_path;
	char	**args;
	char	*tmp;

	if (!arg[0])
		return (NULL);
	args = ft_split(arg, ' ');
	tmp = args[0];
	args[0] = cmd_path(&tmp, npath);
	free(tmp);
	return (args);
}

int	main(int argc, char **argv, char *envp[])
{
	char	**npath;
	
	if (argc < 5)
		exit(EXIT_FAILURE);
	npath = path(envp);
	// atexit(check);
	pipex(argc, argv, npath);
	ft_free(npath);
	free (npath);
	return (0);
}
