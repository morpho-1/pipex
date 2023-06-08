/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylemrab <aylemrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 02:08:25 by aylemrab          #+#    #+#             */
/*   Updated: 2023/06/08 10:38:18 by aylemrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_access(char *join)
{
	int	t_access;

	t_access = 0;
	t_access = access(join, X_OK);
	return (t_access);
}

char	**getpath(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			return (ft_split(env[i] + 5, ':'));
		}
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char **env_paths)
{
	char	*path;
	char	*join_command;

	path = NULL;
	if (env_paths == NULL || !cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{	
		if (check_access(cmd) == 0)
			return (cmd);
		else
			return (NULL);
	}
	join_command = ft_strjoin("/", cmd);
	while (*env_paths)
	{
		path = ft_strjoin(*env_paths, join_command);
		if (check_access(path) == 0)
			break ;
		free(path);
		env_paths++;
	}
	return (path);
}
