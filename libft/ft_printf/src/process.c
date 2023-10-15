 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:15:01 by fvoicu            #+#    #+#             */
/*   Updated: 2023/09/19 06:27:45 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	process_2(char input, t_info *info)
{
	if (input == '-')
		info->flag.left_justify = 1;
	else if (input == '0')
		info->flag.zero_padd = 1;
	else if (input == '+')
		info->flag.show_sign = 1;
	else if (input == '#')
		info->flag.alt_form = 1;
	else if (input == ' ')
		info->flag.space = 1;
}

void	process_3(char input, t_info *info)
{
	info->format.width *= 10;
	info->format.width += (input - '0');
}

void	process_4(t_info *info)
{
	int	i;

	i = va_arg(info->arg, int);
	if (i < 0)
	{
		info->flag.left_justify = 1;
		info->format.width = -i;
	}
	else
		info->format.width = i;
}

void	process_6(char input, t_info *info)
{
	info->format.precision *= 10;
	info->format.precision += (input - '0');
}

void	process_7(t_info *info)
{
	int	arg;

	arg = va_arg(info->arg, int);
	info->format.precision = arg;
}
