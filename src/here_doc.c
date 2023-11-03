/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:58:39 by fvoicu            #+#    #+#             */
/*   Updated: 2023/11/03 01:54:19 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	get_here_doc(char **argv)
{
	char	*line;
	char	*delimiter;
	int		fd[2];

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
