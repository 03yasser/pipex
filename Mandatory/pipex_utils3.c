/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:06:58 by yboutsli          #+#    #+#             */
/*   Updated: 2024/02/09 17:09:30 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	exist_file(char *file)
{
	if (access(file, F_OK) == -1)
		return (0);
	else
		return (1);
}
