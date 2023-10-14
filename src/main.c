/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:46:32 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/14 05:43:41 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>
#include <stdlib.h>

//parsy_parse, get_cmd

// static char	***prep_cmd(t_info *pipex, int arg_idx)
// {
// 	char	**cmd;

// 	if (ft_strncmp(pipex->argv[arg_idx], "./", 2))
// 	{
// 		cmd = ft_split(parsy_parse(pipex->argv[arg_idx]), ' ');
// 		cmd = get_cmd(cmd);
// 	}
// 	else
// 		cmd =
// }

static void	exec_cmd(int *fd, char *cmd_path, char **args, char **env)
{
	char	**cmd;
	char 	*path;
	
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
	// cmd = prep_cmd(cmd_path, args, env);, ' ');
	if (access(cmd, X_OK | F_OK) < 0)
		path = get_path(cmd_path, env);
		
	if (execve (cmd_path, args, env) == -1)
		error("Failed to execute command.", NULL, 1);
}

void	pipex(int *input, char **env, char **argv)
{
	pid_t	pid;
	int		fd[2];
	int		i;

	while (argv [++i + 1])
	{
		if (pipe(fd))
			error("Failed to create pipe.", NULL, 1);
		pid = fork();
		if (pid == -1)
			error("Failed to create subprocess.", NULL, 1);
		if (pid == 0)
		{
			exec_cmd(argv, env, fd); //-->check this out	
			exit (0);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
		if (input)
			free(input);
		input = NULL;
	}
}

int	main(int argc, char **argv, char **env)
{
	char *input;

	if (argc < 4 || (is_here_doc(argv[1]) && argc < 5))
	{
		error("Invalid arguments", NULL, 1);
		return (1);
	}

	input = some_func_i_need;
	if (is_here_doc(argv[1]))
		here_doc(argv++);
	pipex(input, env, arg);
}
