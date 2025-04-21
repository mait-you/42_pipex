/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:19:17 by mait-you          #+#    #+#             */
/*   Updated: 2025/04/14 12:09:40 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_cmd(t_cmd	*cmd)
{
	int	i;

	i = 0;
	printf("path : [%s]\n", cmd->path);
	while (cmd->args[i])
	{
		printf("cmd->args[%d] : {%s}\n", i, cmd->args[i]);
		i++;
	}
	printf("cmd->args[%d] : {%s}\n\n", i, cmd->args[i]);
}

void	error_cleanup(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	child_process(char **av, int *p, char **env)
{
	t_cmd	*cmd;
	int		fd;

	cmd = parse_cmd(av[2], env);
	if (!cmd || !cmd->path)
		error_cleanup(NULL);
	print_cmd(cmd);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (free_cmds(cmd), error_cleanup("open error"));
	dup2(fd, 0);
	dup2(p[1], 1);
	close(p[0]);
	close(fd);
	execve(cmd->path, cmd->args, env);
	free_cmds(cmd);
	exit(1);
}

void	parent_process(char **av, int *p, char **env)
{
	t_cmd	*cmd;
	int		fd;

	cmd = parse_cmd(av[3], env);
	if (!cmd->path)
		error_cleanup("command not found");
	print_cmd(cmd);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (free_cmds(cmd), error_cleanup("open error"));
	dup2(p[0], 0);
	// // dup2(fd, 1);
	close(p[1]);
	close(fd);
	execve(cmd->path, cmd->args, env);
	free_cmds(cmd);
	exit(1);
}

int	main(int ac, char **av, char **env)
{
	int		p[2];
	pid_t	pid;
	int     status;

	if (ac != 5)
		error_cleanup("Usage: ./pipex file1 cmd1 cmd2 file2");
	if (pipe(p) == -1)
		error_cleanup("Error pipe");
	pid = fork();
	if (pid == -1)
		error_cleanup("Fork error");
	if (!pid)
		child_process(av, p, env);
	parent_process(av, p, env);
	waitpid(pid, &status, 0);
	return (1);
}
