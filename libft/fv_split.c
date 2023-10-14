/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fv_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:21:39 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/14 03:58:23 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_slen(char const *str, char c)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		if (*str != c)
		{
			++len;
			while (*str != c && *str)
				++str;
		}
		else
			++str;
	}
	return (len);
}

static char	*get_next_token(char const *s, char c, size_t *position)
{
	size_t	start;
	size_t	end;

	start = *position;
	while (s[start] == c)
		++start;
	end = start;
	while (s[end] != c && s[end])
		++end;
	*position = end;
	return (ft_substr(s, start, end - start));
}

char	**fv_split(char const *s, char c)
{
	size_t	token_count;
	char	**result;
	size_t	position;
	size_t	i;

	token_count = ft_slen(s, c);
	result = (char **)ft_calloc(token_count + 1, sizeof(char *));
	position = 0;
	i = 0;
	if (!s || !result)
		return (NULL);
	while (i < token_count)
	{
		result[i] = get_next_token(s, c, &position);
		if (!result[i])
		{
			while (i--)
				free(result[i]);
			free(result);
			return (NULL);
		}
		++i;
	}
	return (result[i] = NULL, result);
}
