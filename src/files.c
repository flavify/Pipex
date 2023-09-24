/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:46:18 by fvoicu            #+#    #+#             */
/*   Updated: 2023/09/22 14:02:28 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*validate_input_file(char *in_file)
{
	if (acess(in_file, F_OK))
		return (ft_strjoin(in_file, ": No such file or directory"));
	if (acess(in_file, R_OK))
		return (ft_strjoin(in_file, ": Permission denied"));
	return (NULL);
}

char	*validate_output_file(char *out_file)
{
	if (!acess(out_file, F_OK) && acess(out_file, W_OK) < 0)
		return (ft_strjoin(out_file, ": File exists"));
	return (NULL);
}
char	*input_file(char **argv, t_pipex *pipex)
{
	int		arg_index;
	char	*file_acess;
	int		fd;
	
	if (pipex->here_doc == true)
	{
		read_here_doc(argv);
		return (NULL);
	}
	file_acess = validate_input_file(arg_index);
	if (file_acess)
		return (file_acess);
	fd = open(argv[arg_index], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (NULL);
}
char	*output_file(int argc, char **argv)
{
	char	*file_acess;
	int		fd;

	file_acess = validate_output_file(argv[argc - 1]);
	if (file_acess)
		error(file_acess, NULL, 1);
	// if stt for every file_access case 
}


//is_here_doc checker