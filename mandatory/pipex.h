/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:38:23 by mait-you          #+#    #+#             */
/*   Updated: 2025/02/12 16:18:08 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

# ifndef PATH
#  define PATH "PATH="
# endif

// Structure to hold command information
typedef struct s_cmd
{
	char	*path;
	char	**args;
}			t_cmd;

// Function prototypes
void	free_cmds(t_cmd	*cmd);
void	free_args(char **ar);
t_cmd	*parse_cmd(char *cmd_str, char **env);
char	*find_path(char *cmd, char **env);
void	error_cleanup(const char *msg);

void	print_cmd(t_cmd	*cmd);

#endif
