/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 04:38:52 by fvoicu            #+#    #+#             */
/*   Updated: 2023/09/20 15:02:45 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	adjust_padding(size_t nbr, t_info *info, \
	int *padd_printing_len)
{
	if ((info->spec == 'd' || info->spec == 'i') && info->nbr.sign < 0)
		*padd_printing_len -= 1;
	else if ((info->spec == 'd' || info->spec == 'i') && info->flag.show_sign)
		*padd_printing_len -= 1;
	else if ((info->spec == 'd' || info->spec == 'i') && !info->flag.show_sign
		&&info->flag.space)
		*padd_printing_len -= 1;
	else if ((info->spec == 'x' || info->spec == 'X') && info->flag.alt_form
		&& nbr != 0)
		*padd_printing_len -= 2;
	else if (info->spec == 'p')
		*padd_printing_len -= 2;
}

void	handle_special_flags(size_t nbr, t_info *info)
{
	if (info->nbr.sign < 0 && info->flag.zero_padd == true)
		info->count += write(STDOUT_FILENO, "-", 1);
	else if (info->nbr.sign >= 0 && info->flag.show_sign
		&& info->format.width > 1 && info->flag.zero_padd == true)
	{	
		info->count += write(STDOUT_FILENO, "+", 1);
		info->printed.sign = true;
	}
	if (info->nbr.sign >= 0 && info->flag.space && !info->flag.show_sign
		&& info->flag.zero_padd == true)
		info->count += write(STDOUT_FILENO, " ", 1);
	if (info->flag.alt_form && info->flag.zero_padd == true)
	{
		if (info->spec == 'x' && nbr != 0)
			info->count += write(STDOUT_FILENO, "0x", 2);
		else if (info->spec == 'X' && nbr != 0)
			info->count += write(STDOUT_FILENO, "0X", 2);
		info->printed.prefix = true;
	}
}
