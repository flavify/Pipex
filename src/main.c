/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:46:32 by fvoicu            #+#    #+#             */
/*   Updated: 2023/09/24 05:20:55 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex(t_info *pipex, char	*input, char	**argv, char **env, char *output)
{
	if (pipe(pipex->fds) == -1)
	{
		perror("pipe");
		exit(1);
	}

	pipex->pid = fork();
	
	if (pipex->pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (pipex->pid == 0)
	{
		dup2(pipex->fds[0], STDOUT_FILENO);
		close(pipex->fds[0]);
		close(pipex->fds[1]);
		
		*output = open(output, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (!output)
		{
			perror("open");
			exit(1);
		}
		dup2(output, STDOUT_FILENO);
		close(output);
		execve(input, argv, env);
		perror("execve");
		exit(1);	
	}
	dup2(pipex->fds[1], STDIN_FILENO);
	close(pipex->fds[0]);
	close(pipex->fds[1]);

	waitpid(pipex->pid, NULL, 0);
	*input = open(input, O_RDONLY);
	dup2(input, STDIN_FILENO);
	close(input); 

	execve(output, argv, env);
	perror("execve");
	exit(1);
}

# include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_info	pipex;
	char	*input;
	char	*output;
	
	if (argc != 5)
	{
		write(2, "Invalid number of arguments\n", 28);
		exit(1);
	}
	
	input = argv[1];
	output = argv[argc - 1];
	
	pipex(argv[2], argv + 2, env, argv[3]);
	return (0);
}