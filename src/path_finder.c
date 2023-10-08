/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 00:21:44 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/07 21:54:43 by fvoicu           ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
{
	char	*st;

	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			st = (char *)s;
			return (&st[0]);
		}
		s++;
	}
	if (*s == (char)c)
	{
		return (&(*(char *)s));
	}
	return (NULL);
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

char	*fv_strtok(char *str, const char *delim)
{
	static char	*buff;
	char		*token_start;

	if (str)
		buff = str;
	if (!buff || !delim)
		return (NULL);
	while (*buff && ft_strchr(delim, *buff))
		++buff;
	if (!(*buff))
		return (NULL);
	token_start = buff;
	while (*buff && !ft_strchr(delim, *buff))
		++buff;
	if (*buff)
	{
		*buff = '\0';
		++buff;
	}
	return (token_start);
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

char	*get_path(char *arg, char **env)
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
			break ;
		}
		++i;
	}
	if (!path)
		return (NULL);
	token = fv_strtok(path, ":");
	while (token)
	{
		full_path = fv_strjoin_and_free(ft_strjoin(token, "/"), arg);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free (full_path);
		token = fv_strtok(NULL, ":");
	}
	return (NULL);
}

#include <stdio.h>
#include <stdlib.h>

// Assuming you have necessary function prototypes above
// ...

int main(int argc, char **argv, char **envp) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    char *command_path = get_path(argv[1], envp);
    if (command_path) {
        printf("Path for command %s: %s\n", argv[1], command_path);
        free(command_path);  // Don't forget to free the memory!
    } else {
        printf("Command %s not found in PATH.\n", argv[1]);
    }

    return 0;
}
