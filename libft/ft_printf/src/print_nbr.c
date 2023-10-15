/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:04:18 by fvoicu            #+#    #+#             */
/*   Updated: 2023/09/20 15:02:29 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static void	get_nbr_info(size_t *nbr, t_info *info)
{
	info->nbr.sign = get_sign(nbr, info->spec);
	info->nbr.base = get_base(info->spec);
	info->nbr.len = get_number_len(*nbr, info->nbr.base);
}

static void	print_zero_padding(t_info *info, int nbr_printing_len)
{
	int	zero_printing_len;

	zero_printing_len = nbr_printing_len - info->nbr.len;
	while (zero_printing_len > 0)
	{
		info->count += write(STDOUT_FILENO, "0", 1);
		--zero_printing_len;
	}
}

static void	print_nbr_by_type(size_t nbr, t_info *info)
{
	char	*buff;
	char	*baseset;
	size_t	nbr_backup;

	buff = (char *)malloc(sizeof(char) * (info->nbr.len + 1));
	if (!buff)
		return ;
	buff[info->nbr.len] = '\0';
	nbr_backup = nbr;
	baseset = base_set(info->spec);
	while (info->nbr.len > 0)
	{
		buff[info->nbr.len - 1] = baseset[nbr % info->nbr.base];
		nbr /= info->nbr.base;
		--(info->nbr.len);
	}
	if (!(nbr_backup == 0 && info->format.precision == 0))
	{
		ft_putstr_fd(buff, STDOUT_FILENO);
		info->count += ft_strlen(buff);
	}
	free(buff);
}

static void	print_nbr_by_prec(size_t nbr, t_info *info, int print_len)
{
	if (!info->printed.sign)
	{	
		if (info->nbr.sign < 0 && !info->flag.zero_padd)
			info->count += write(STDOUT_FILENO, "-", 1);
		else if (info->nbr.sign >= 0 && info->flag.show_sign)
			info->count += write(STDOUT_FILENO, "+", 1);
		else if (info->nbr.sign >= 0 && info->flag.space
			&& !info->flag.show_sign && !info->flag.zero_padd)
			info->count += write(STDOUT_FILENO, " ", 1);
	}
	if (!info->printed.prefix)
	{
		if (info->spec == 'p')
			info->count += write(STDOUT_FILENO, "0x", 2);
		else if (info->spec == 'x' && info->flag.alt_form && nbr != 0)
			info->count += write(STDOUT_FILENO, "0x", 2);
		else if (info->spec == 'X' && info->flag.alt_form && nbr != 0)
			info->count += write(STDOUT_FILENO, "0X", 2);
	}
	print_zero_padding(info, print_len);
	print_nbr_by_type(nbr, info);
}

void	print_nbr(size_t nbr, t_info *info)
{
	int	nbr_printing_len;
	int	padd_printing_len;

	get_nbr_info(&nbr, info);
	if ((info->format.precision < info->nbr.len)
		&& !(info->format.precision == 0 && nbr == 0))
		nbr_printing_len = info->nbr.len;
	else
		nbr_printing_len = info->format.precision;
	padd_printing_len = info->format.width - nbr_printing_len;
	adjust_padding(nbr, info, &padd_printing_len);
	handle_special_flags(nbr, info);
	if (info->flag.left_justify == true)
	{
		print_nbr_by_prec(nbr, info, nbr_printing_len);
		print_padding(info, padd_printing_len);
	}
	else
	{
		print_padding(info, padd_printing_len);
		print_nbr_by_prec(nbr, info, nbr_printing_len);
	}
}
