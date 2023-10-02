/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:46:32 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/01 21:56:29 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex(t_info *pipex, char	*input, char	**argv, char **env, char *output)
{
	if (pipe(pipex->fds) == -1) // create pipe and store de fds 
	{
		perror("pipe");
		exit(1);
	}
//EYYYY
	pipex->pid = fork();// create child process and store pid
	
	if (pipex->pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (pipex->pid == 0) // child process
	{
		dup2(pipex->fds[0], STDOUT_FILENO); // redirect stdout to write end of pipe
		// close(pipex->fds[0]);
		close(pipex->fds[1]); // close both ends of pipe
		
		*output = open(output, O_CREAT | O_WRONLY | O_TRUNC, 0777);// opening the output file with the right perms
		if (!output)
		{
			perror("open");
			exit(1);
		}
		dup2(output, STDOUT_FILENO); // redirect stdout to output file
		close(output); // close output file
		execve(input, argv, env); // execute the command
		perror("execve");
		exit(1);	
	}
	// parent process
	dup2(pipex->fds[1], STDIN_FILENO); // redirect stdin to read end of pipe
	close(pipex->fds[0]); 
	// close(pipex->fds[1]); // close both ends of pipe

	waitpid(pipex->pid, NULL, 0); // wait for child process to finish
	*input = open(input, O_RDONLY); // open input file
	dup2(input, STDIN_FILENO); // redirect stdin to input file
	close(input); // close input file

	execve(output, argv, env); // execute the command
	perror("execve");
	exit(1);
}

# include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*output;
	
	
	if (argc < 5)
	{
		write(2, "Invalid number of arguments\n", 28);
		exit(1);
	}
	
	input = argv[1];
	output = argv[argc - 1];

	pipex(argv[2] , input, argv[3], env, output); //change this 
	return (0);
}