/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:49:20 by fvoicu            #+#    #+#             */
/*   Updated: 2023/05/21 19:24:16 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static size_t	ft_slen(char const *str, char c)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		if (*str != c)
		{
			len++;
			while (*str != c && *str)
				str++;
		}
		else
			str++;
	}
	return (len);
}

static char	*ft_sstr(char const *s, char c, size_t j)
{
	size_t	i;
	size_t	count;
	char	*str;

	str = NULL;
	i = -1;
	count = -1;
	while (++i < (size_t)ft_strlen(s) && s[i])
	{
		if (s[i] != c)
			count++;
		if (count == j && s[i] != c)
		{
			count = i;
			while (s[count] && s[count] != c)
				count++;
			str = ft_substr(s, i, count - i);
			if (!str)
				return (NULL);
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	s_size;
	char	**ptr;

	i = 0;
	s_size = ft_slen(s, c);
	ptr = (char **)ft_calloc(s_size + 1, sizeof(char *));
	if (!s || !ptr)
		return (NULL);
	if (c == '\0' && ft_strlen(s) > 0)
		s_size = 1;
	while (i < s_size)
	{
		ptr[i] = ft_sstr(s, c, i);
		if (!ptr[i])
		{
			while (i--)
				free (ptr[i]);
			free (ptr);
			return (NULL);
		}
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
