/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:09:03 by fvoicu            #+#    #+#             */
/*   Updated: 2023/11/02 00:26:42 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void exec(char *av, char **env)
{
	char **cmd;
	char *binary;
	
	cmd = ft_split(av, " ");
	if (!cmd)
		error("Error getting commands", NULL, 1);
	binary = get_path(cmd[0], env);
	if (!binary)
	{
		fv_free_array(cmd);
		error("Command not found", cmd, 1);
	}
	if (execve(binary, cmd, env) == -1)
	{
		free(binary);
		fv_free_array(cmd);
		error("Error executing command", NULL, 1);
	}
}

static void child(char *cmd, char **env, int *p_fd)
{
	if (close(p_fd[0]) == -1)
		error("Error closing pipe read end.", NULL, 1);
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
		error("Error duplicating pipe write end.", NULL, 1);
	exec(cmd, env);
}

static void	parent(int *p_fd, pid_t *pid)
{
	if (close(p_fd[1]) == -1)
		error("Error closing pipe write end.", NULL, 1);
	if (dup2(p_fd[0], STDIN_FILENO) == -1)
		error("Error duplicating pipe read end.", NULL, 1);
	if (waitpid(*pid, NULL, 0) == -1)
		error("Error waiting for child process.", NULL, 1);
	if (close(p_fd[0]) == -1)
		error("Error closing pipe read end.", NULL, 1);
	
	del_info(); // this!!
}

static void	pipex(char *cmd, char **env)
{
	int p_fd[2];
	pid_t pid;

	if (pipe(p_fd) == -1)
		error("Error creating pipe.", NULL, 1);
	pid = fork();
	if (pid == -1)
		error("Error creating child process.", NULL, 1);
	if (pid == 0)
		child(cmd, env, p_fd);
	else
		parent(p_fd, &pid);
}

void	exec_cmds(t_info *info)
{
	int i;

	i = 1;
	if (info->here_doc)
		i = 2;
	while (++i < info->ac - 2)
		pipex(info->av[i], info->env);
	if (dup2(info->out_fd, STDOUT_FILENO) == -1)
		error("Error duplicating output file descriptor.", NULL, 1);
	exec(info->av[info->ac -2], info->env);
}