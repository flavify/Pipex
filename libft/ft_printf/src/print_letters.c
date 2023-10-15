/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_letters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 06:24:11 by fvoicu            #+#    #+#             */
/*   Updated: 2023/09/20 13:26:58 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	print_char(char c, t_info *info)
{
	int	padding_len;

	padding_len = info->format.width - 1;
	if (info->flag.left_justify == true)
	{
		put_char(c, info);
		print_padding(info, padding_len);
	}
	else
	{
		print_padding(info, padding_len);
		put_char(c, info);
	}
}

static void	print_precise_string(t_info *info, char *str, int str_printing_len)
{
	int	i;

	i = 0;
	while (i < str_printing_len)
	{
		put_char(str[i], info);
		++i;
	}
}

void	print_str(char *str, t_info *info)
{
	int	string_printing_len;
	int	padding_len;

	if (str == NULL)
		str = "(null)";
	if (info->format.precision == -1
		|| (size_t)info->format.precision > ft_strlen(str))
		string_printing_len = ft_strlen(str);
	else
		string_printing_len = info->format.precision;
	padding_len = info->format.width - string_printing_len;
	if (info->flag.left_justify == true)
	{
		print_precise_string(info, str, string_printing_len);
		print_padding(info, padding_len);
	}
	else
	{
		print_padding(info, padding_len);
		print_precise_string(info, str, string_printing_len);
	}
}

void	print_padding(t_info *info, int padding_len)
{
	char	padding;

	if (info->flag.zero_padd == true && info->spec != 's')
		padding = '0';
	else
		padding = ' ';
	if (info->flag.zero_padd == true && \
		(info->spec == '%' && info->flag.left_justify == true))
		padding = ' ';
	while (padding_len > 0)
	{
		put_char(padding, info);
		--padding_len;
	}
}
