/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:58:39 by fvoicu            #+#    #+#             */
/*   Updated: 2023/11/02 03:55:17 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// static bool is_here_doc(t_info *pipex, char **argv)
// {
// 	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
// 		return (pipex->here_doc = true);
// 	return (pipex->here_doc = false);
// }

void	get_here_doc(char **argv)
{
	char	*line;
	char	*delimiter;
	int 	fd[2];

	if (pipe(fd))
	{
		perror("here_doc");
		exit(1);
	}

	delimiter = ft_strjoin(argv[2], "\n");
	line = get_next_line(0);
	while (line && ft_strncmp(delimiter, line, ft_strlen(line)))
	{
		ft_putstr_fd(line, fd[1]);
		free(line);
		line = get_next_line(0);
	}

	free(delimiter);

	if (line)
		free(line);

	dup2(fd[0], 0);
	close(fd[0]); 	
	close(fd[1]);
}


