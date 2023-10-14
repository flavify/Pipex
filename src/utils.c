/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:02:22 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/14 05:24:15 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//TO DO: ft_strncmp doesn t handle the case where s1 is shorter than s2 -->falsely evaluating to true
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
bool	is_here_doc(const char *arg)
{
	return (!ft_strncmp(arg, "here_doc", 9));
}

char	*parsy_parse(const char *input)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!result)
		error("malloc", NULL, 1);
	while (input[i])
	{
		if (!fv_is_space(input[i]))
		{
			if (j > 0 && fv_is_space(input[i - 1]))
				result[j++] = ' ';
			result[j++] = input[i];
		}
		i++;
	}
	if (j > 0 && result[j - 1] == ' ')
		j--;
	result[j] = '\0';
	return (result);
}
