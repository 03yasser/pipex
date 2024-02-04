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

#include "pipex.h"
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
	int	i;
	char	*tmp;
	char	*tmp1;

	if (**cmd == '\0')
		return (NULL);
	tmp = ft_strtrim(*cmd);
	if (tmp)
	{
		tmp1 = *cmd;
		*cmd = tmp; 
		free(tmp1);
	}	
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
void child_process1(int fd[2], int fd1, char *argv, char **npath)
{
	char	**execv_args;
	execv_args = execv_argv(argv, npath);
	dup2(fd1, 0);
	dup2(fd[1], 1);
	close (fd1);
	close(fd[0]);
	close(fd[1]);
	execv(execv_args[0], execv_args);
	
}
void	child_process2(int fd[2], int fd2, char *argv, char **npath)
{
	char	**execv_args;

	dup2(fd2, 1);
	dup2(fd[0], 0);
	close(fd2);
	close(fd[0]);
	close(fd[1]);
	execv_args = execv_argv(argv, npath);
	execv(execv_args[0], execv_args);
}
int	*middle_procees()
{
	
}	
void	pipex_uils(int read, char *argv, char **npath)
{
	int	pid;
	int	fd[2];
	pipe(fd);
	pid = fork()
	if(pid == 0)
	{
		
	}


}
void	pipex(int argc, char **argv, char **npath)
{
	int	fd[2];
	int	tmp[2];
	int	pid;
	int	pid1;
	int	fd1;
	int	fd2;
	int	i;
	fd1 = file1(argv[1]);
	fd2 = file2(argv[argc - 1]);
	if (fd1 < 0 || fd2 < 0)
		return ;
	pipe(fd);
	// pipe fail
	pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	if (pid == 0)
		child_process1(fd, fd1, argv[2], npath);
	waitpid(pid, NULL, 0);
	i = 3;
	while (i < argc - 1)
	{
		pipex_utils()
	}
	pid1 = fork();
	if (pid1 < 0)
		return (perror("Fork: "));
	if (pid1 == 0)
		child_process2(fd, fd2, argv[3], npath);
	close(fd1);
	close(fd2);
}

char **execv_argv(char *arg, char **npath)
{
	char	*cmd;
	char	*ccmd_path;
	char	**args;
	char	*tmp;


	args = ft_split(arg, ' ');
	tmp = args[0];
	args[0] = cmd_path(&tmp,npath);
	if (args[0] == NULL)
	{
		
	}
	free(tmp);
	return(args);
}
int	main(int argc, char **argv, char *envp[])
{
	char	**npath;
	if (argc != 5)
		return (0);
	npath = path(envp);
	// atexit(check);
	pipex(argc, argv, npath);
	ft_free(npath);
	free (npath);
	return (0);
}
