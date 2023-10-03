/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:03:26 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/03 15:17:39 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>


typedef struct s_info
{
	int		argc;
	char	**cmd_path;
	char	**cmd_arg;
	int		fds[2];
	bool	here_doc;
	pid_t	pid;
}	t_info;

// file_validators
char	*validate_input_file(char *in_file);
char	*validate_input_file(char *out_file);
char	*input_file(char **arg, t_info *pipex);
char	*output_file(int argc, char **argv);

//error_handling
void	error(char *msg, char **cmd, int exit_code);

//exec
void	pipex(t_info *pipex, char	*input, char	**argv, char **env, char *output);


#endif