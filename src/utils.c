/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:02:22 by fvoicu            #+#    #+#             */
/*   Updated: 2023/11/02 00:40:14 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_info	init_info(int ac, char **av, char **env)
{
	t_info info;
	
	info.av = av;
	info.env = env;
	info.ac = ac;
	info.in_fd = 0;
	info.out_fd = 0;
	info.p_fd[0] = 0;
	info.p_fd[1] = 0;
	info.here_doc = false;
	return (info);
}
void	error(char *error, char **cmd, int exit_code)
{
	char	*message;

	if (cmd != NULL)
	{
		fv_free_array(cmd);
	}
	message = fv_strjoin_and_free("Error: ", error);
	ft_putendl_fd(message, 2);
	free(message);
	exit(exit_code);
}
