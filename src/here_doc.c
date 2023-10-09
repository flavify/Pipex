/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:58:39 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/09 19:25:46 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static bool is_here_doc(t_info *pipex, char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		return (pipex->here_doc = true);
	return (pipex->here_doc = false);
}

void	get_here_doc(char **argv)
{
	char	*line;
	char	*delimiter;
	int 	fd[2];

	if (pipe(fd))
		{
			perror("here_doc");
			return (NULL);
			exit (1);
		}
	delimiter = ft_strjoin(argv[2], "\n");
	line = get_next_line(0);
	while (line && ft_strncmp(delimiter, line, ft_strlen(line)))
	{
		ft_putstr_fd(line, fd[1]);
		free (line);
		line = get_next_line(0);
	}
	free (delimiter);
	if (line)
		free (line);
	dup2(fd[0], 0);
	close(fd[0]); 	
	close(fd[1]);
}

#include <stdio.h>
#include <stdlib.h>

// Assuming you have the necessary headers and declarations included.

int main(int argc, char **argv)
{
    t_info pipex;
    
    if (argc < 3)
    {
        write(2, "Provide 'here_doc' and a delimiter.\n", 36);
        exit(1);
    }
    
    is_here_doc(&pipex, argv);

    if (pipex.here_doc)
    {
        get_here_doc(argv);

        // Print the content of the here doc to validate:
        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1)) > 0)
        {
            buffer[bytes_read] = '\0';
            printf("%s", buffer);
        }
    }
    else
    {
        printf("Not a heredoc.\n");
    }

    return 0;
}
