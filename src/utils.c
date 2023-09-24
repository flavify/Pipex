/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:02:22 by fvoicu            #+#    #+#             */
/*   Updated: 2023/09/22 13:45:28 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//perror
void	error(char *msg, char **cmd, int exit_code)
{
	char	*error;

	if (cmd != NULL)
	{
		free_array(cmd);
	}
	error = msg;
	msg = ft_strjoin_and_free("Error: ", error);
	ft_putendl_fd(msg, 2);
	free(msg);
	exit(exit_code);
}
