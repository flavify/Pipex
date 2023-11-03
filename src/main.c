/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:46:32 by fvoicu            #+#    #+#             */
/*   Updated: 2023/11/03 05:08:36 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_info	info;

	if (ac < 5 || ((ft_strncmp("here_doc", av[1], 9) == 0) && ac < 6))
		error("Invalid arguments", NULL, 1);
	info = init_info(ac, av, envp);
	if (ft_strncmp("here_doc", av[1], 9) == 0)
	{
		info.here_doc = true;
		get_here_doc(av);
		info.out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (info.out_fd == -1)
			error("Failed to open output file.", NULL, 1);
	}
	else
	{
		info.out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (info.out_fd == -1)
			error("Failed to open output file.", NULL, 1);
		info.in_fd = open(av[1], O_RDONLY);
		if (info.in_fd == -1)
		{
			perror("pipex: input");
			info.in_fd = open("/dev/null", O_RDONLY);
			if (info.in_fd == -1)
				error("Error: Failed to open /dev/null.", NULL, 1);
		}
		if (dup2(info.in_fd, STDIN_FILENO) == -1)
			error("Failed to duplicate input file descriptor.", NULL, 1);
	}
	exec_cmds(&info);
	return (0);
}
