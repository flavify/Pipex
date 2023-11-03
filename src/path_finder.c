/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 00:21:44 by fvoicu            #+#    #+#             */
/*   Updated: 2023/11/03 01:58:41 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h" 

static char	*construct_path(char *directory, char *arg)
{
	char	*base_path;
	char	*cmd_path;

	base_path = ft_strjoin(directory, "/");
	if (!base_path)
		return (NULL);
	cmd_path = fv_strjoin_and_free(base_path, arg);
	if (!cmd_path)
	{
		free(base_path);
		return (NULL);
	}
	return (cmd_path);
}

static char	*check_path(char *path, char *arg)
{
	char	*token;
	char	*full_path;

	token = fv_strtok(path, ":");
	while (token)
	{
		full_path = construct_path(token, arg);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		token = fv_strtok(NULL, ":");
	}
	return (NULL);
}

char	*get_path(char *arg, char **env)
{
	char	*path;

	path = NULL;
	if (!env || !arg)
		return (ft_strdup(arg));
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env + 5;
			if (path)
				return (check_path(path, arg));
			break ;
		}
		++env;
	}
	return (ft_strdup(arg));
}
