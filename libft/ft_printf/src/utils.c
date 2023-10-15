/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:15:46 by fvoicu            #+#    #+#             */
/*   Updated: 2023/09/20 13:21:55 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	put_char(char c, t_info *info)
{
	write(STDOUT_FILENO, &c, 1);
	++(info->count);
}

int	get_sign(size_t *nbr, char spec)
{
	if ((spec == 'd' || spec == 'i') && (int)*nbr < 0)
	{
		*nbr *= -1;
		return (-1);
	}
	return (1);
}

int	get_base(char spec)
{
	if (spec == 'd' || spec == 'i' || spec == 'u')
		return (10);
	else
		return (16);
}

int	get_number_len(size_t number, int base)
{
	int		len;

	if (number == 0)
		return (1);
	len = 0;
	while (number)
	{
		++len;
		number /= base;
	}
	return (len);
}

char	*base_set(char spec)
{
	if (spec == 'd' || spec == 'i' || spec == 'u')
		return ("0123456789");
	else if (spec == 'x' || spec == 'p')
		return ("0123456789abcdef");
	else
		return ("0123456789ABCDEF");
}
