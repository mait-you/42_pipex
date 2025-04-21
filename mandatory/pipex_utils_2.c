/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:26:00 by mait-you          #+#    #+#             */
/*   Updated: 2025/02/12 16:35:30 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_args(char **ar)
{
	while (*ar)
	{
		free(*ar);
		ar++;
	}
}

void	free_cmds(t_cmd	*cmd)
{
	if (!cmd)
		return ;
	if (cmd->path)
		free(cmd->path);
	if (cmd->args)
		free_args(cmd->args);
	free(cmd);
}
