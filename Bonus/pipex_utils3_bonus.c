/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:04:32 by yboutsli          #+#    #+#             */
/*   Updated: 2024/02/10 22:15:45 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char	**execv_argv(char *arg, char **npath)
{
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

int	exist_file(char *file)
{
	if (access(file, F_OK) == -1)
		return (0);
	else
		return (1);
}

void	child_process2(char *cmd, char **npath)
{
	char	**execv_args;
	int		pid;

	if (!cmd[0])
	{
		write(2, "permission denied\n", 18);
		exit(EXIT_FAILURE);
	}
	execv_args = execv_argv(cmd, npath);
	pid = fork();
	if (pid == 0)
		execv(execv_args[0], execv_args);
	ft_free(execv_args);
	close(0);
	while (waitpid(0, 0, 0) != -1)
		;
}
