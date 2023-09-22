/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by flaviav           #+#    #+#             */
/*   Updated: 2023/09/21 15:22:59 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_after_nl(char *res)
{
	char	*line;
	char	*tmp;

	tmp = res;
	while (*tmp && *tmp != '\n'
		&& ((unsigned long)(tmp - res) < ft_strlen(res)))
		tmp++;
	if (!*tmp)
		return (free(res), res = NULL, NULL);
	tmp++;
	line = ft_calloc(ft_strlen(tmp)+ 1, sizeof(char));
	ft_strlcpy(line, tmp, ft_strlen(tmp) + 1);
	return (free(res), res = NULL, line);
}

static char	*build_res(char *buff)
{
	char	*line;
	char	*tmp;
	char	orig_char;

	if (!buff)
		return (NULL);
	tmp = buff;
	while (*tmp && *tmp != '\n')
		tmp++;
	if (*tmp == '\n')
		tmp++;
	orig_char = *tmp;
	*tmp = '\0';
	line = ft_calloc(ft_strlen(buff) + 1, sizeof(char));
	if (!line)
	{
		*tmp = orig_char;
		return (NULL);
	}
	ft_strlcpy(line, buff, ft_strlen(buff) + 1);
	*tmp = orig_char;
	return (line);
}

static char	*build_buffer(int fd, char *res)
{
	char	*buff;
	int		bytes_read;

	if (!(res))
		res = ft_calloc(1, sizeof(char));
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (free(res), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0 && (!(res) || (res)[0] == '\0'))
			return (free(buff), free(res), NULL);
		buff[bytes_read] = '\0';
		res = fv_strjoin_and_free(res, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (free(buff), res);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(res), res = NULL, NULL);
	res = build_buffer(fd, res);
	if (!res)
		return (NULL);
	line = build_res(res);
	if (!line)
		return (NULL);
	res = extract_after_nl(res);
	return (line);
}
		