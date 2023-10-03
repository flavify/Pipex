/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 00:21:44 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/04 01:00:10 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/pipex.h" 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int		i;

	i = 0;
	while (s1[i] && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s2[i] == '\0' || i == n)
		return (0);
	else
		return (-s2[i]);
}

char *fv_strtok(char *str, const char *delim) {
    static char *buffer;
    char *token_start, *ptr;
    
    if (str)
        buffer = str;
    if (!buffer || !delim)
        return NULL;

    for ( ; *buffer != '\0'; buffer++) {
        ptr = strchr(delim, *buffer);
        if (ptr == NULL)
            break;
    }
    if (*buffer == '\0') 
        return NULL;

    token_start = buffer;

    for ( ; *buffer != '\0'; buffer++) {
        ptr = strchr(delim, *buffer);
        if (ptr != NULL) {
            *buffer = '\0';
            buffer++;
            break;
        }
    }
    return token_start;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*s;

	s = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (*(s1 + i))
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (*(s2 + j))
	{
		s[i] = s2[j];
		i++;
		j++;
	}
	s[i] = 0;
	return (s);
}

char	*fv_strjoin_and_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

char *find_command_path(char *arg, char **env)
{
	char	*path;
	char	*full_path;
	int		i;
	char	*token;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break;
		}
		++i;
	}
	if (!path)
		return (NULL);
	token = strtok(path, ":");
	while (token)
	{
		full_path = fv_strjoin_and_free(ft_strjoin(token, "/"), arg);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free (full_path);
		token = strtok(NULL, ":");
	}
	return (NULL);
}


#include <stdio.h>

// Assume you've included the necessary headers and have the find_command_path function defined above.

int main() {
    // Mock environment, typically you'd get this from the 3rd argument to main in a real program.
    char *mock_env[] = {
        "HOME=/home/user",
        "PATH=/usr/bin:/bin:/usr/local/bin",
        "LOGNAME=user",
        NULL // Terminating NULL pointer
    };

    // List of commands to search for
    char *commands[] = {
        "ls",
        "gcc",
        "nonexistent_command", // This one shouldn't be found
        "cat",
        NULL // Terminating NULL pointer
    };

    for (int i = 0; commands[i]; i++) {
        char *path = find_command_path(commands[i], mock_env);
        if (path) {
            printf("%s found at: %s\n", commands[i], path);
            free(path); // Don't forget to free the allocated path after using it
        } else {
            printf("%s not found in PATH\n", commands[i]);
        }
    }

    return 0;
}
