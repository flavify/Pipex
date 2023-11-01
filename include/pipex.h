/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:03:26 by fvoicu            #+#    #+#             */
/*   Updated: 2023/11/02 00:52:20 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>


typedef struct s_info
{
	char	**av;
	char	**env;
	int 	ac;
	int		in_fd;
	int		out_fd;
	int		p_fd[2];
	bool	here_doc;
}	t_info;

t_info	init_info(int ac, char **av, char **envp);

// file_validators
char	*validate_input_file(char *in_file);
char	*validate_input_file(char *out_file);
char	*input_file(char **arg, t_info *pipex);
char	*output_file(int argc, char **argv);

//error_handling
void	error(char *msg, char **cmd, int exit_code);

//get_path 
char	*get_path(char *arg, char **env);

//exec
void	pipex(t_info *pipex, char	*input, char	**argv, char **env, char *output);


#endif