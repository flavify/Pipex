/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:02:22 by fvoicu            #+#    #+#             */
/*   Updated: 2023/11/03 03:30:39 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_info	init_info(int ac, char **av, char **env)
{
	t_info	info;

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

void	error(const char *msg, const char *cmd_name, int exit_status)
{
	char	*message;
	char	*temp;
	int		i;

	i = 2;
	if (cmd_name)
	{
		message = ft_strjoin("pipex: ", cmd_name);
		temp = message;
		message = ft_strjoin(temp, ": ");
		free(temp);
		temp = message;
		message = ft_strjoin(temp, msg);
		free(temp);
	}
	else
		message = ft_strjoin("pipex: ", msg);
	ft_putendl_fd(message, 2);
	free(message);
	while (++i < 30)
		close(i);
	exit(exit_status);
}
