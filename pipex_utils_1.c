/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:26:00 by mait-you          #+#    #+#             */
/*   Updated: 2025/04/12 13:54:45 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **env)
{
	char	*path;
	char	**tmp;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], PATH, 5) == 0)
		{
			path = env[i] + 5;
			break ;
		}
		i++;
	}
	tmp = ft_split(path, ':');
	while (tmp && tmp[i])
	{
		path = ft_strjoin(tmp[i], cmd);
		if (!access(path, X_OK))
			return (free_args(tmp), free(cmd), path);
		free(path);
		i++;
	}
	return (free(cmd), NULL);
}

t_cmd	*parse_cmd(char *cmd_str, char **env)
{
	t_cmd	*cmd;
	char	reject;

	if (!cmd_str || !*cmd_str)
		return (NULL);
	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_split(cmd_str, ' ');
	if (!access(cmd->args[0], X_OK))
		cmd->path = ft_strdup(cmd->args[0]);
	else
		cmd->path = find_path(ft_strjoin("/", cmd->args[0]), env);
	return (cmd);
}
