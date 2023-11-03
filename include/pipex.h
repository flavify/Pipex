/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:03:26 by fvoicu            #+#    #+#             */
/*   Updated: 2023/11/03 03:33:00 by fvoicu           ###   ########.fr       */
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
# include "libft.h"
# include <stdio.h>


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

void	exec_cmds(t_info *info);
void	get_here_doc(char **argv);
char	*get_path(char *arg, char **env);
void	error(const char *msg, const char *cmd_name, int exit_status);

#endif