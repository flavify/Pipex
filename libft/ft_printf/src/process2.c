/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 06:25:08 by fvoicu            #+#    #+#             */
/*   Updated: 2023/09/20 14:28:22 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	process_8(t_info *info)
{
	if ((info->flag.left_justify == true || info->format.precision > -1))
		info->flag.zero_padd = false;
	if (info->flag.show_sign == true)
		info->flag.space = false;
	if (info->spec == 'c')
		print_char(va_arg(info->arg, int), info);
	else if (info->spec == 's')
		print_str(va_arg(info->arg, char *), info);
	else if (info->spec == 'p')
		print_nbr(va_arg(info->arg, unsigned long), info);
	else if (info->spec == 'd' || info->spec == 'i')
		print_nbr(va_arg(info->arg, int), info);
	else if (info->spec == 'u' || info->spec == 'x' || info->spec == 'X')
		print_nbr(va_arg(info->arg, unsigned int), info);
	else if (info->spec == '%')
		print_char('%', info);
	reset_info(info);
}
