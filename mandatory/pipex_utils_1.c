/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:26:00 by mait-you          #+#    #+#             */
/*   Updated: 2025/02/12 16:35:21 by mait-you         ###   ########.fr       */
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

void	chek_cmd(t_cmd	*cmd)
{
	int		i;
	int		j;
	size_t	key;

	i = 0;
	while (cmd->args[i])
	{
		j = 0;
		key = 0;
		while (cmd->args[i][j])
		{
			if (cmd->args[i][j] == ' ')
				key++;
			j++;
		}
		if (ft_strlen(cmd->args[i]) == key)
		{
			free(cmd->args[i + 1]);
			free(cmd->args[i]);
			cmd->args[i] = NULL;
			return ;
		}
		i++;
	}
}

void	get_clean_cmd(t_cmd	*cmd, const char *cmd_str, char reject)
{
	int		len;
	char	*clean_cmd;
	char	*ptr;

	cmd->args = ft_split(cmd_str, reject);
	ptr = *cmd->args;
	while (*ptr && *ptr == ' ')
		ptr++;
	len = 0;
	while (ptr[len] && ptr[len] != ' ')
		len++;
	clean_cmd = ft_substr(ptr, 0, len);
	free(*cmd->args);
	*cmd->args = clean_cmd;
	chek_cmd(cmd);
}

char	ft_get_reject(const char *cmd_str)
{
	while (*cmd_str)
	{
		if (*cmd_str == '"')
			return ('"');
		if (*cmd_str == '\'')
			return ('\'');
		cmd_str++;
	}
	return (' ');
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
	reject = ft_get_reject(cmd_str);
	if (reject == '"')
		get_clean_cmd(cmd, cmd_str, '"');
	else if (reject == '\'')
		get_clean_cmd(cmd, cmd_str, '\'');
	else
		cmd->args = ft_split(cmd_str, ' ');
	if (!access(cmd->args[0], X_OK))
		cmd->path = ft_strdup(cmd->args[0]);
	else
		cmd->path = find_path(ft_strjoin("/", cmd->args[0]), env);
	return (cmd);
}
