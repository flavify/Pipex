/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:41:34 by fvoicu            #+#    #+#             */
/*   Updated: 2023/09/21 15:23:32 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static size_t	size(int n)
{
	size_t	size;

	size = 0;
	if (n < 0)
	{
		size++;
		n = -n;
	}
	if (n == 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	n_size;
	int		tmp;

	tmp = n;
	n_size = size(n);
	str = (char *)malloc(sizeof(char) * n_size + 1);
	if (!str)
		return (NULL);
	if (n == -2147483648)
		return ((char *)ft_memmove(str, "-2147483648", 12));
	str[n_size--] = '\0';
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	while (n_size > 0)
	{
		str[n_size--] = (n % 10) + '0';
		n = n / 10;
	}
	if (tmp >= 0)
		str[n_size] = n + '0';
	return (str);
}
