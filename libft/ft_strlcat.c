/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:28:15 by fvoicu            #+#    #+#             */
/*   Updated: 2023/05/21 15:15:04 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t n)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = 0;
	src_len = 0;
	while ((*src || src) && dst_len < n && *dst)
	{
		dst++;
		dst_len++;
	}
	if (dst_len == n)
		return (ft_strlen(src) + dst_len);
	while (src[src_len])
	{
		if (src_len < n - dst_len - 1)
			*dst++ = src[src_len];
		src_len++;
	}
	*dst = '\0';
	return (dst_len + src_len);
}
