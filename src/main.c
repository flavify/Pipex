/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:46:32 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/12 15:47:44 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>
#include <stdlib.h>

//parsy_parse, get_cmd

static char	***prep_cmd(t_info *pipex, int arg_idx)
{
	char	**cmd;

	if (ft_strncmp(pipex->argv[arg_idx], "./", 2))
	{
		cmd = ft_split(parsy_parse(pipex->argv[arg_idx]), ' ');
		cmd = get_cmd(cmd);
	}
	else
		cmd = 
}

static void	exec_cmd(t_info *pipex, char **args, char **env)
{
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	if (pipex->fd[0] != STDIN_FILENO)
		close(pipex->fd[0]);
	if (pipex->fd[1] != STDOUT_FILENO)
		close(pipex->fd[1]);
	execve (pipex->cmd_path, args, env);
	perror ("execve"); 
	exit (1);
}

void	pipex(t_info *pipex, char **env, char *input, char *output)
{
	int prev_fd;
	int i;	
	
	i = 2;
	pipex->pid = malloc (sizeof(int) * (pipex->argc - 3));
	while (i < (pipex->argc - 1))
	{
		pipex->cmd_path = get_path(pipex->argv[i], env);
		
		pipe(pipex->fd);
		
		if (!(pipex->pid = fork()))
		{
			if(prev_fd != -1)
				close(prev_fd);			
		}
		
		
		++i;
	}
}

















void	pipex(t_info *pipex, char	*input, char	**argv, char **env, char *output)
{
	int	fd_in;
	int	fd_out;
	int	prev_pipe_read_end;
	int	i;
	char	*cmd_path;

	i = 2; //index for argv
	prev_pipe_read_end = -1; //For first command ---> input file
	while (i < pipex->argc - 1)
	{
		cmd_path = get_path(argv[i], env);
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
			execve(cmd_path, argv + i, env);
			perror("execve");
			exit(1);
		}
		else //-->parent
		{
			close(pipex->fds[1]);
			if (prev_pipe_read_end != -1)
				close(prev_pipe_read_end);
			prev_pipe_read_end = pipex->fds[0];	
		}
		free(cmd_path);
		++i; // --->next command
	}
	i = 2; //reset counter
	while (i < pipex->argc - 1)
	{
		wait(NULL); //wait for all children to finish
		++i;
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

// #include <stdio.h>

// extern char **environ;

// int main(void)
// {
//     t_info pipex_info;
//     char *input = "input.txt";
//     char *output = "output.txt";
//     char *argv[] = {"pipex", "cat", "grep test", NULL}; // pipex is just a placeholder for argv[0]
//     char **env = environ;


//     pipex(&pipex_info, input, argv, env, output);

//     // Read the output file to see if it contains the line with "test".
//     FILE *fp = fopen(output, "r");
//     char line[256];
//     while (fgets(line, sizeof(line), fp)) {
//         printf("%s", line); // Should print "this is a test" if everything worked correctly
//     }
//     fclose(fp);

//     return 0;
// }
