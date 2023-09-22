/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:30:33 by fvoicu            #+#    #+#             */
/*   Updated: 2023/05/20 07:15:10 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t d_size)
{
	size_t	s_size;
	size_t	i;

	s_size = ft_strlen(src);
	i = 0;
	if (!dst || !src)
		return (0);
	if (d_size != 0)
	{
		while (src[i] != '\0' && i < (d_size -1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (s_size);
}
