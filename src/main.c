/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:46:32 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/03 15:19:31 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>
#include <stdlib.h>
// change execvp to execve

void	pipex(t_info *pipex, char	*input, char	**argv, char **env, char *output)
{
	int	fd_in;
	int	fd_out;
	int	prev_pipe_read_end;
	int	i;

	i = 2; //index for argv
	prev_pipe_read_end = -1; //For first command ---> input file
	while (i < pipex->argc - 1)
	{
		pipe(pipex->fds);
		if (!(pipex->pid = fork())) //-->child
		{
			if (prev_pipe_read_end != -1) //not first command
			{
				dup2(prev_pipe_read_end, STDIN_FILENO);
				close(prev_pipe_read_end);
			}
			else //for 1st command read from input file
			{
				fd_in = open(input, O_RDONLY);
				if (fd_in < 0)
				{
					perror("open input");
					exit(1);
				}
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			if (i != pipex->argc - 2) // Not last command
				dup2(pipex->fds[1], STDOUT_FILENO);
			else // For last commnd, write to output file
			{
				fd_out = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (fd_out < 0)
				{
					perror("open output");
					exit(1);
				}
				dup2(fd_out, STDOUT_FILENO);
				close(fd_out);
			}
			close(pipex->fds[0]);
			close(pipex->fds[1]);
			execvp(argv[i], argv + i);
			perror("execvp");
			exit(1);
		}
		else //-->parent
		{
			close(pipex->fds[1]);
			if (prev_pipe_read_end != -1)
				close(prev_pipe_read_end);
			prev_pipe_read_end = pipex->fds[0];	
		}
		i++; // --->next command
	}
	i = 2; //reset counter
	while (i < pipex->argc - 1)
	{
		wait(NULL); //wait for all children to finish
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_info t_pipex;
	char *input;
	char *output;
	
	if (argc < 5)
	{
		write(2, "Invalid number of arguments\n", 28);
		exit(1);
	}
	t_pipex.argc = argc;
	t_pipex.cmd_path = argv;
	t_pipex.cmd_arg = argv + 2;
	t_pipex.here_doc = false;
	
	input = argv[1];
	output = argv[argc - 1];

	pipex(&t_pipex , input, argv, env, output);
	return (0);
}